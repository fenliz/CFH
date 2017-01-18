#pragma once
#include "..\Threading\SharedMutex.h"
#include "LogOutput.h"

#include <map>
#include <sstream>

namespace CFH
{
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

