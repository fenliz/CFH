#include "File.h"
#include "Core\Logging\Log.h"

#include <fstream>

namespace CFH
{
	bool File::Exist(const std::string& path)
	{
		std::ifstream file(path.c_str());
		return file.good();
	}

	std::string File::ReadText(const std::string& path, bool throwException) 
		throw(FileNotFoundException)
	{
		std::string result;
		std::ifstream fileStream;
		fileStream.open(path, std::fstream::in);
		ASSERT(fileStream.is_open());
		if (fileStream.is_open())
		{
			std::string line;
			while (std::getline(fileStream, line))
			{
				result += line;
				if (!fileStream.eof())
					result += "\n";
			}
			fileStream.close();
		}
		else
		{
			LOG_DEBUG("Could not open file: '" + path + "'");

			if (throwException)
				throw FileNotFoundException();
		}
	}

	std::string File::GetPath(const std::string& path)
	{
		return path.substr(0, path.find_last_of("/\\") + 1);
	}
	std::string File::GetFilename(const std::string& path)
	{
		return path.substr(path.find_last_of("/\\") + 1);
	}
	std::string File::GetFilenameWithoutExtension(const std::string& path)
	{
		std::string filename = GetFilename(path);
		return filename.substr(0, filename.find_last_of("."));
	}
	std::string File::GetExtension(const std::string& path)
	{
		return path.substr(path.find_last_of(".") + 1);
	}
}