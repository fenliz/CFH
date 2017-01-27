#include "Profiler.h"
#include "CFH.Core\CFH.h"
#include "CFH.Core\Threading\Thread.h"
#include "CFH.Core\Messaging\Message.h"

namespace CFH
{
	Profiler::Profiler() :
		current_(nullptr),
		root_(nullptr)
	{
		current_ = root_ = new ProfilerBlock(nullptr, "Frame");

		SUBSCRIBE_TO_MESSAGE(FrameBeginMessage, this, [this](FrameBeginMessage message) { OnBeginFrame(); });
		SUBSCRIBE_TO_MESSAGE(FrameEndMessage, this, [this](FrameEndMessage message) { OnEndFrame(); });
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

	Profiler* Profiler::GetInstance()
	{
		static Profiler instance;
		return &instance;
	}

	real32 Profiler::GetFrameTime() const
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