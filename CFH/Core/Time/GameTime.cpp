#include "GameTime.h"
#include "..\EngineContext.h"
#include "..\Messages\Message.h"

namespace CFH
{
	GameTime::GameTime(EngineContext* context)
	{
		context->GetMessageBus()->Subscribe<EndFrameMessage>(this, [this](EndFrameMessage message) { OnEndFrame(); });
		context->GetMessageBus()->Subscribe<BeginFrameMessage>(this, [this](BeginFrameMessage message) { OnBeginFrame(); });
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