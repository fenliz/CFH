#include "Application.h"
#include "Time\GameTime.h"
#include "EngineContext.h"
#include "Log\Logger.h"

namespace CFH
{
	Application::Application()
	{
		ENABLE_DEBUG_CONSOLE_LOGGING();

		engineContext_ = new EngineContext();
		gameTime_ = new GameTime(engineContext_);
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		LOG_DEBUG("Application: Run");

		if (!isRunning_)
			return;

		isRunning_ = true;
		while (isRunning_)
		{
			Update();
			Render();
			_sleep(100);
		}
	}

	void Application::Update()
	{
		engineContext_->GetMessageBus()->Send<BeginFrameMessage>(BeginFrameMessage());

		engineContext_->GetMessageBus()->Send<EndFrameMessage>(EndFrameMessage());
	}

	void Application::Render()
	{
	}
}
