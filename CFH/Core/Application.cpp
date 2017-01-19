#include "Application.h"
#include "Messaging\Messages.h"
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
		SUBSCRIBE_TO_MESSAGE(WindowCloseMessage, this, [this](WindowCloseMessage message) { Stop(); });

		gameTime_ = new GameTime(engineContext_);
		window_ = new Window(engineContext_);
	}
	Application::~Application()
	{
	}

	void Application::Initialize(int width, int height, LPWSTR title)
	{
		window_->Initialize(width, height, title);
	}

	void Application::Update()
	{
		SEND_DEFAULT_MESSAGE(FrameBeginMessage);

		for (auto update : updateSubscribers_)
			update(gameTime_);

		SEND_DEFAULT_MESSAGE(FrameEndMessage);
	}
	void Application::Render()
	{
		for (auto render : renderSubscribers_)
			render();
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

	void Application::UpdateSubscribe(UpdateFunction function)
	{
		mutex_.LockExclusive();
		updateSubscribers_.push_back(function);
		mutex_.UnlockExclusive();
	}
	void Application::RenderSubscribe(RenderFunction function)
	{
		mutex_.LockExclusive();
		renderSubscribers_.push_back(function);
		mutex_.UnlockExclusive();
	}
}
