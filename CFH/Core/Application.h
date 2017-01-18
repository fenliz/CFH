#pragma once
#include "..\CFH.h"
#include "Threading\SharedMutex.h"

#include <atomic>

namespace CFH
{
	class Window;
	class GameTime;
	class EngineContext;

	// Central application object, the entry point to starting
	// an instance of the engine.
	class CFH_API Application
	{
	public:
		Application();
		~Application();

		void Start();
		void Stop();

		bool IsRunning() const;

	private:
		std::atomic<bool> isRunning_;
		Window* window_;
		GameTime* gameTime_;
		EngineContext* engineContext_;

		void Update();
		void Render();
	};
}

