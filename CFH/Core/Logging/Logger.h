#pragma once
#include "..\Threading\SharedMutex.h"

#include <iostream>
#include <vector>

namespace CFH
{
#define LOG_ERROR(text) \
	Logger::GetInstance().Log(LoggingSeverity::Error, text)
#define LOG_WARNING(text) \
	Logger::GetInstance().Log(LoggingSeverity::Warning, text)
#define LOG_INFO(text) \
	Logger::GetInstance().Log(LoggingSeverity::Info, text)
#define LOG_DEBUG(text) \
	Logger::GetInstance().Log(LoggingSeverity::Debug, text)

#define LOG_ERROR_IF(condition, text) \
	if (condition) LOG_ERROR(text)
#define LOG_WARNING_IF(condition, text) \
	if (condition) LOG_WARNING(text)
#define LOG_INFO_IF(condition, text) \
	if (condition) LOG_INFO(text)
#define LOG_DEBUG_IF(condition, text) \
	if (condition) LOG_DEBUG(text)

#define ENABLE_DEBUG_CONSOLE_LOGGING() \
	Logger::GetInstance().AddOutput(new ConsoleLogOutput(LoggingSeverity::Debug))

	enum LoggingSeverity
	{
		None = 0,
		Error = 1,
		Warning = 2,
		Info = 3,
		Debug = 4
	};
	class LogOutput
	{
	public:
		LogOutput(LoggingSeverity severity) :
			Severity(severity) { }

		virtual void Write(const char* text) const {};

		LoggingSeverity Severity;
	};

	class Logger
	{
	public:
		~Logger() 
		{
			for (auto& it : outputs_)
				delete it;
		}

		void AddOutput(LogOutput* output)
		{
			mutex.LockExclusive();
			outputs_.push_back(output);
			mutex.UnlockExclusive();
		}

		void Log(LoggingSeverity severity, const char* text)
		{
			mutex.LockShared();
			for (auto& it : outputs_)
			{
				if (it->Severity >= severity)
					it->Write(text);
			}
			mutex.LockShared();
		}

		static Logger& GetInstance()
		{
			static Logger instance;
			return instance;
		}

	private:
		Logger() = default;
		Logger(const Logger&) = delete;

		std::vector<LogOutput*> outputs_;
		SharedMutex mutex;
	};

	class ConsoleLogOutput : public LogOutput
	{
	public:
		ConsoleLogOutput(LoggingSeverity severity) :
			LogOutput(severity) { }

		virtual void Write(const char* text) const
		{
			std::cout << text << std::endl;
		}
	};
}

