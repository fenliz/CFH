#include "Application.h"
#include "Messaging\MessageBus.h"
#include "EngineContext.h"
#include "Timing\GameTime.h"
#include "Logging\Logger.h"
#include "Window.h"

namespace CFH
{
	Application::Application()
	{
		engineContext_ = new EngineContext();
		ENABLE_CONSOLE_LOGGING(LoggingSeverity::Debug);

		gameTime_ = new GameTime(engineContext_);
		window_ = new Window(engineContext_);
		window_->Initialize(800, 600, L"CFH Application");
	}
	Application::~Application()
	{
	}

	void Application::Update()
	{
		SEND_DEFAULT_MESSAGE(BeginFrameMessage);

		SEND_DEFAULT_MESSAGE(EndFrameMessage);
	}

	void Application::Render()
	{
	}

	void Application::Start()
	{
		LOG_DEBUG("Application: Start");

		if (!IsRunning())
			return;

		window_->Show();

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		isRunning_ = true;
		while (isRunning_)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			Update();
			Render();
			_sleep(100);
		}
	}

	void Application::Stop()
	{
		LOG_DEBUG("Application: Stop");
		isRunning_ = false;
	}

	bool Application::IsRunning() const
	{
		return isRunning_;
	}
}
