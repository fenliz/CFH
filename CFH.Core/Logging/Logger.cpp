#include "Logger.h"
#include "CFH.Core\IO\File.h"
#include "CFH.Core\Timing\Time.h"

#include <sstream>

namespace CFH
{
	Logger* Logger::GetInstance()
	{
		static Logger instance;
		return &instance;
	}

	void Logger::Register(LogOutput* output, Severity severity)
	{
		mutex_.LockExclusive();
		outputs_.insert(std::make_pair(output, severity));
		mutex_.UnlockExclusive();
	}

	void Logger::Log(Severity severity, std::string& message,
					 const char* function, const char* file, int line)
	{
		std::string timestamp = Time::GetTimestamp();
		std::string filename = File::GetFilename(std::string(file));

		mutex_.LockShared();
		for (auto& it : outputs_)
		{
			if (it.second <= severity)
				it.first->Write(message, timestamp, function, filename, line);
		}
		mutex_.LockShared();
	}
}