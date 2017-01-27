#include "File.h"
#include "CFH.Core\CFH.h"

#include <fstream>

#define FILEIO_NOT_IMPLEMENTED "File IO is not implemented on this platform."

namespace CFH
{
	PGETSIZEFUNC(GetSizeStub) { LOG_ERROR(FILEIO_NOT_IMPLEMENTED); return 0; }
	GETSIZEFUNC* File::GetSize = GetSizeStub;

	PREADFUNC(ReadStub) { LOG_ERROR(FILEIO_NOT_IMPLEMENTED); return false; }
	READFUNC* File::Read = ReadStub;

	PWRITEFUNC(WriteStub) { LOG_ERROR(FILEIO_NOT_IMPLEMENTED); return false; }
	WRITEFUNC* File::Write = WriteStub;

	bool32 File::Exist(const std::string& path)
	{
		std::ifstream file(path);
		return file.good();
	}

	std::string File::GetPath(const std::string& path)
	{
		std::string string(path);
		return string.substr(0, string.find_last_of("/\\") + 1).c_str();
	}
	std::string File::GetFilename(const std::string& path)
	{
		std::string string(path);
		return string.substr(string.find_last_of("/\\") + 1);
	}
	std::string File::GetFilenameWithoutExtension(const std::string& path)
	{
		std::string filename = GetFilename(path);
		return filename.substr(0, filename.find_last_of("."));
	}
	std::string File::GetExtension(const std::string& path)
	{
		std::string string(path);
		return string.substr(string.find_last_of(".") + 1);
	}
}