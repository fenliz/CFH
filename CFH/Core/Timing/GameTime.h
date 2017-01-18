#pragma once
#include "..\..\CFH.h"
#include "Timer.h"

namespace CFH
{
	class EngineContext;
	class BeginFrameMessage;

	// Central time object that tracks the time of a frame
	// and is used to manipulating time in the engine.
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

