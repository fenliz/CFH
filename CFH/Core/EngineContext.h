#pragma once
#include "..\CFH.h"

namespace CFH
{
	class Logger;
	class MessageBus;
	class Profiler;

	/* a core context in the engine holding central object
	 that could be needed everywhere in the engine. for the
	 moment most of these classes are accessed by static instances
	 but the context handles the creation / destruction of them.*/
	class CFH_API EngineContext
	{
	public:
		EngineContext();
		~EngineContext();

	private:
		Logger* logger_;
		MessageBus* messageBus_;
		Profiler* profiler_;
	};
}

