#pragma once
#include "CFH.Core\Types.h"

#include <string>

#define PGETSIZEFUNC(name) uint32 name(const char* path)
typedef PGETSIZEFUNC(GETSIZEFUNC);

#define PREADFUNC(name) bool32 name(const char* path, void* memory, uint32* size)
typedef PREADFUNC(READFUNC);

#define PWRITEFUNC(name) bool32 name(const char* path, void* memory, uint32 size)
typedef PWRITEFUNC(WRITEFUNC);

namespace CFH
{
	class CFHCORE_API File
	{
	public:
		static GETSIZEFUNC* GetSize;
		static READFUNC* Read;
		static WRITEFUNC* Write;

		static bool32 Exist(const std::string& path);

		static std::string GetPath(const std::string& path);
		static std::string GetFilename(const std::string& path);
		static std::string GetFilenameWithoutExtension(const std::string& path);
		static std::string GetExtension(const std::string& path);
	};
}