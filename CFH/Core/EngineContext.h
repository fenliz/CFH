#pragma once
#include "Messaging\MessageBus.h"
#include "Profiling\Profiler.h"

namespace CFH
{
	class CFH_API EngineContext
	{
	public:
		EngineContext();
		~EngineContext();

		MessageBus* GetMessageBus();

	private:
		MessageBus* messageBus_;
		Profiler* profiler_;
	};
}

