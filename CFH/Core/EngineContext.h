#pragma once
#include "Core\Messages\MessageBus.h"

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
	};
}

