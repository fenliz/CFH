#pragma once
#include "..\CFH.h"

namespace CFH
{
	class GameTime;
	class EngineContext;

	// Central application object, the entry point to starting
	// an instance of the engine.
	class CFH_API Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		bool isRunning_;
		GameTime* gameTime_;
		EngineContext* engineContext_;

		void Update();
		void Render();
	};
}

