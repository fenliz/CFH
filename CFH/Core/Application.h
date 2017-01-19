#pragma once
#include "..\CFH.h"
#include "Threading\SharedMutex.h"

#include <atomic>
#include <vector>
#include <functional>

namespace CFH
{
	class Window;
	class GameTime;
	class EngineContext;

	typedef std::function<void()> RenderFunction;
	typedef std::function<void(GameTime*)> UpdateFunction;

	// Central application object, the entry point to starting
	// an instance of the engine.
	class Application
	{
	public:
		CFH_EXPORT Application();
		CFH_EXPORT ~Application();

		void CFH_EXPORT Initialize(int width, int height, LPWSTR title);

		void CFH_EXPORT Start();
		void CFH_EXPORT Stop();

		bool CFH_EXPORT IsRunning() const;

		void CFH_EXPORT UpdateSubscribe(UpdateFunction function);
		void CFH_EXPORT RenderSubscribe(RenderFunction function);

	private:
		std::vector<UpdateFunction> updateSubscribers_;
		std::vector<RenderFunction> renderSubscribers_;
		SharedMutex mutex_;

		std::atomic<bool> isRunning_;
		Window* window_;
		GameTime* gameTime_;
		EngineContext* engineContext_;

		void Update();
		void Render();
	};
}

