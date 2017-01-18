#include "Profiler.h"
#include "ProfilerBlock.h"
#include "..\Threading\Thread.h"
#include "..\Messaging\MessageBus.h"

#include <string>

namespace CFH
{
	Profiler* Profiler::instance_ = nullptr;

	Profiler::Profiler(EngineContext* context) :
		current_(nullptr),
		root_(nullptr)
	{
		instance_ = this;

		current_ = root_ = new ProfilerBlock(nullptr, "Frame");

		SUBSCRIBE_TO_MESSAGE(BeginFrameMessage, this, [this](BeginFrameMessage message) { OnBeginFrame(); });
		SUBSCRIBE_TO_MESSAGE(EndFrameMessage, this, [this](EndFrameMessage message) { OnEndFrame(); });
	}
	Profiler::~Profiler()
	{
	}

	void Profiler::BeginBlock(const char* name)
	{
		if (!Thread::IsMainThread())
			return;

		current_ = current_->GetChild(name);
		current_->Begin();
	}
	void Profiler::EndBlock()
	{
		if (!Thread::IsMainThread())
			return;

		current_->End();

		ProfilerBlock* parent = current_->GetParent();
		if (parent)
			current_ = parent;
	}

	void Profiler::BeginInterval()
	{
		root_->BeginInterval();
		intervalFrames_ = 0;
	}

	const ProfilerBlock* Profiler::GetCurrentBlock() const
	{
		return current_;
	}
	const ProfilerBlock* Profiler::GetRootBlock() const
	{
		return root_;
	}

	Profiler* Profiler::GetInstance() const
	{
		return instance_;
	}

	float Profiler::GetFrameTime()
	{
		return (root_->GetFrameTime() / 100000.0f);
	}

	void Profiler::OnBeginFrame()
	{
		if (root_->IsActive())
			OnEndFrame();
		root_->Begin();
	}
	void Profiler::OnEndFrame()
	{
		EndBlock();
		intervalFrames_++;
		root_->EndFrame();
		current_ = root_;
	}
}


