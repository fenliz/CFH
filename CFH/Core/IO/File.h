#pragma once
#include "CFH.h"
#include "Core\Exceptions.h"

#include <string>

namespace CFH
{
	class CFH_API File
	{
	public:
		static bool Exist(const std::string& path);

		static std::string ReadText(const std::string& path,
			bool throwException = false) throw(FileNotFoundException);

		static std::string GetPath(const std::string& path);
		static std::string GetFilename(const std::string& path);
		static std::string GetFilenameWithoutExtension(const std::string& path);
		static std::string GetExtension(const std::string& path);
	};
}