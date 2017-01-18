#pragma once
#include "..\CFH.h"

namespace CFH
{
	class GameTime;
	class EngineContext;

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

