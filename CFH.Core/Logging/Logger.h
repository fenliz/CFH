#pragma once
#include "LogOutput.h"
#include "CFH.Core\Threading\SharedMutex.h"

#include <sstream>
#include <map>

namespace CFH
{
#define LOGGER_MESSAGE(message) static_cast<std::ostringstream&>(std::ostringstream().flush() << message << std::endl).str()

	// Convencience macros for logging information.
#define LOG_ERROR(message) \
	Logger::GetInstance()->Log(Logger::Severity::Error, LOGGER_MESSAGE(message), __FUNCTION__, __FILE__, __LINE__) 
#define LOG_WARNING(message) \
	Logger::GetInstance()->Log(Logger::Severity::Warning, LOGGER_MESSAGE(message), __FUNCTION__, __FILE__, __LINE__) 
#define LOG_INFO(message) \
	Logger::GetInstance()->Log(Logger::Severity::Info, LOGGER_MESSAGE(message), __FUNCTION__, __FILE__, __LINE__) 
#define LOG_DEBUG(message) \
	Logger::GetInstance()->Log(Logger::Severity::Debug, LOGGER_MESSAGE(message), __FUNCTION__, __FILE__, __LINE__) 

#define LOG_ERROR_IF(condition, message) \
	if (condition) LOG_ERROR(message)
#define LOG_WARNING_IF(condition, message) \
	if (condition) LOG_WARNING(message)
#define LOG_INFO_IF(condition, message) \
	if (condition) LOG_INFO(message)
#define LOG_DEBUG_IF(condition, message) \
	if (condition) LOG_DEBUG(message)

	// Convenience macro for enabling the logger to write to the console with a specific severity.
#define ENABLE_CONSOLE_LOGGING(severity) \
	Logger::GetInstance()->Register(new ConsoleLogOutput(), severity)


	// Logs information and outputs it to registered logoutputs.
	class Logger
	{
	public:
		// The different severities that a logoutput may be interested of.
		// By choosing a number the log will receive all messages of that severity and higher.
		enum class CFHCORE_API Severity
		{
			Debug = 1,
			Info = 2,
			Warning = 3,
			Error = 4
		};

		static CFHCORE_API Logger* GetInstance();

		// Registers a new ouput to the logger, the output will receive all messages
		// of that severity and higher.
		void CFHCORE_API Register(LogOutput* output, Severity severity);

		// Logs information at a specific severity to all registered outputs with thread-safety.
		void CFHCORE_API Log(Severity severity, std::string& message,
							 const char* function, const char* file, int line);

	private:
		Logger() {}
		~Logger() {}
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		std::map<LogOutput*, Severity> outputs_;
		SharedMutex mutex_;
	};
}

