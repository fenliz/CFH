#include "Logger.h"

namespace CFH
{
	Logger* Logger::instance_ = nullptr;

	Logger::Logger()
	{
		ASSERT(!instance_);
		instance_ = this;
	}
	Logger::~Logger()
	{
		for (auto it : outputs_)
			delete it.first;
	}

	Logger* Logger::GetInstance()
	{
		return instance_;
	}

	void Logger::Register(LogOutput* output, LoggingSeverity severity)
	{
		mutex.LockExclusive();
		outputs_.insert(std::make_pair(output, severity));
		mutex.UnlockExclusive();
	}
}