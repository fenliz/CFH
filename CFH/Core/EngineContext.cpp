#include "EngineContext.h"

namespace CFH
{
	EngineContext::EngineContext()
	{
		messageBus_ = new MessageBus();
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
