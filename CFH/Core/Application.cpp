#include "Application.h"
#include "Messaging\MessageBus.h"
#include "EngineContext.h"
#include "Timing\GameTime.h"
#include "Logging\Logger.h"

namespace CFH
{
	Application::Application()
	{
		engineContext_ = new EngineContext();
		ENABLE_CONSOLE_LOGGING(LoggingSeverity::Debug);

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
		SEND_DEFAULT_MESSAGE(BeginFrameMessage);

		SEND_DEFAULT_MESSAGE(EndFrameMessage);
	}

	void Application::Render()
	{
	}
}
