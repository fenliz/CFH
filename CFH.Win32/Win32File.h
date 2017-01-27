#pragma once
#include "CFH.Core\CFH.h"
#include "CFH.Core\IO\File.h"

#include <Windows.h>
#include <limits>

namespace CFH
{
	class Win32File
	{
	public:
		static void Setup()
		{
			File::GetSize = Win32File::GetSize;
			File::Read = Win32File::Read;
			File::Write = Win32File::Write;
		}

		static PGETSIZEFUNC(GetSize)
		{
			HANDLE file = CreateFileA(path, GENERIC_READ,
									  FILE_SHARE_READ,
									  nullptr,
									  OPEN_EXISTING,
									  FILE_ATTRIBUTE_NORMAL,
									  nullptr);

			if (file == INVALID_HANDLE_VALUE)
			{
				LOG_WARNING("File " << path << " not found");
				return 0;
			}

			uint64 result = 0;
			LARGE_INTEGER size;
			if (GetFileSizeEx(file, &size))
				result = size.QuadPart;

			LOG_ERROR_IF(result <= UINT_MAX, "Cannot get size of file that is larger than INT32MAX");

			CloseHandle(file);
			return (uint32)result;
		}

		static PREADFUNC(Read)
		{
			HANDLE file = CreateFileA(path, GENERIC_READ,
									  FILE_SHARE_READ,
									  nullptr,
									  OPEN_EXISTING,
									  FILE_ATTRIBUTE_NORMAL,
									  nullptr);

			if (file == INVALID_HANDLE_VALUE)
			{
				LOG_ERROR("File " << path << " could not be found/opened for reading.");
				return false;
			}

			bool32 result = false;
			LARGE_INTEGER fileSize;
			if (GetFileSizeEx(file, &fileSize))
			{

				LOG_ERROR_IF(fileSize.QuadPart <= UINT_MAX, "Cannot get read file that is larger than INT32MAX");
				DWORD bytesRead;
				if (ReadFile(file, memory, (uint32)fileSize.QuadPart,
							 &bytesRead, 0))
				{
					if (bytesRead == fileSize.QuadPart)
					{
						*size = (uint32)fileSize.QuadPart;
						result = true;
					}
				}
			}

			if (!result)
				LOG_ERROR("Could not read file " << path);

			CloseHandle(file);
			return true;
		}

		static PWRITEFUNC(Write)
		{
			HANDLE file = CreateFileA(path, GENERIC_WRITE,
									  0,
									  nullptr,
									  CREATE_ALWAYS,
									  0,
									  nullptr);

			if (file == INVALID_HANDLE_VALUE)
			{
				LOG_ERROR("File " << path << " could not be found/opened for writing.");
				return false;
			}

			bool32 result = false;
			DWORD bytesWritten;
			if (WriteFile(file, memory, size, &bytesWritten, 0))
			{
				if (bytesWritten == size)
					result = true;
			}

			if (!result)
				LOG_ERROR("Could not write to file " << path);

			CloseHandle(file);
			return result;
		}
	};
}