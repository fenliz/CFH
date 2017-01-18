#include "EngineContext.h"
#include "Messaging\MessageBus.h"
#include "Profiling\Profiler.h"
#include "Threading\Thread.h"

namespace CFH
{
	EngineContext::EngineContext()
	{
		Thread::SetAsMainThread();

		messageBus_ = new MessageBus();
		profiler_ = new Profiler(this);
	}
	EngineContext::~EngineContext()
	{
		delete messageBus_;
	}

	MessageBus* EngineContext::GetMessageBus()
	{
		return messageBus_;
	}
}
