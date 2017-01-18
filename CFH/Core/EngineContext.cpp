#include "EngineContext.h"
#include "Messaging\MessageBus.h"
#include "Profiling\Profiler.h"
#include "Threading\Thread.h"
#include "Logging\Logger.h"

namespace CFH
{
	EngineContext::EngineContext()
	{
		Thread::SetAsMainThread();

		logger_ = new Logger();
		messageBus_ = new MessageBus();
		profiler_ = new Profiler(this);
	}
	EngineContext::~EngineContext()
	{
		delete logger_;
		delete messageBus_;
		delete profiler_;
	}
}
