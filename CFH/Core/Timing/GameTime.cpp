#include "GameTime.h"
#include "Core\EngineContext.h"
#include "Core\Messaging\Messages.h"

namespace CFH
{
	GameTime::GameTime(EngineContext* context)
	{
		SUBSCRIBE_TO_MESSAGE(FrameBeginMessage, this, [this](FrameBeginMessage message) { OnBeginFrame(); });
	}
	GameTime::~GameTime()
	{
	}

	float GameTime::GetDeltaTime()
	{
		return lastFrame_;
	}
	float GameTime::GetElapsedTime()
	{
		return elapsedTimer_.GetMilliSeconds() / 1000.0f;
	}
	unsigned int GameTime::GetFrameNumber()
	{
		return frameNumber_;
	}

	void GameTime::OnBeginFrame()
	{
		frameNumber_++;
		lastFrame_ = elapsedTimer_.GetMilliSeconds() / 1000.0f;
		elapsedTimer_.Reset();
	}

	void GameTime::OnEndFrame()
	{
		int i = 0;
	}
}