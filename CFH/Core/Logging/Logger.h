#pragma once
#include "..\Threading\SharedMutex.h"
#include "LogOutput.h"
#include "Log.h"

#include <map>
#include <sstream>

namespace CFH
{
	// Convencience macros for logging information.
#define LOG_ERROR(text) \
	Logger::GetInstance()->Log(LoggingSeverity::Error, text)
#define LOG_WARNING(text) \
	Logger::GetInstance()->Log(LoggingSeverity::Warning, text)
#define LOG_INFO(text) \
	Logger::GetInstance()->Log(LoggingSeverity::Info, text)
#define LOG_DEBUG(text) \
	Logger::GetInstance()->Log(LoggingSeverity::Debug, text)

#define LOG_ERROR_IF(condition, text) \
	if (condition) LOG_ERROR(text)
#define LOG_WARNING_IF(condition, text) \
	if (condition) LOG_WARNING(text)
#define LOG_INFO_IF(condition, text) \
	if (condition) LOG_INFO(text)
#define LOG_DEBUG_IF(condition, text) \
	if (condition) LOG_DEBUG(text)

	// Convenience macro for enabling the logger to write to the console with a specific severity.
#define ENABLE_CONSOLE_LOGGING(severity) \
	Logger::GetInstance()->Register(new ConsoleLogOutput(), severity)

	// The different severities that a logoutput may be interested of.
	// By choosing a number the log will receive all messages of that severity and higher.
	enum LoggingSeverity
	{
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4
	};

	// Logs information and outputs it to registered logoutputs.
	class Logger
	{
	public:
		Logger();
		~Logger();

		static Logger* GetInstance();

		// Registers a new ouput to the logger, the output will receive all messages
		// of that severity and higher.
		void Register(LogOutput* output, LoggingSeverity severity);

		// Logs information at a specific severity to all registered outputs with thread-safety.
		template <class T>
		void Log(LoggingSeverity severity, T message)
		{
			std::ostringstream string;
			string << message;

			mutex.LockShared();
			for (auto& it : outputs_)
			{
				if (it.second <= severity)
					it.first->Write(string.str());
			}
			mutex.LockShared();
		}

	private:
		Logger(const Logger&) = delete;
		static Logger* instance_;

		std::map<LogOutput*, LoggingSeverity> outputs_;
		SharedMutex mutex;
	};
}

