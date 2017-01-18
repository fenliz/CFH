#pragma once
#include "..\..\CFH.h"
#include "Timer.h"

namespace CFH
{
	class EngineContext;
	class BeginFrameMessage;

	class CFH_API GameTime
	{
	public:
		GameTime(EngineContext* context);
		~GameTime();

		float GetDeltaTime();
		float GetElapsedTime();
		unsigned int GetFrameNumber();

	private:
		Timer elapsedTimer_;
		Timer frameTimer_;
		float lastFrame_;
		unsigned int frameNumber_;

		void OnBeginFrame();
		void OnEndFrame();
	};
}

