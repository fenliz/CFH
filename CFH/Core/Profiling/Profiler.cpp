#include "Profiler.h"
#include "..\Threading\Thread.h"
#include "..\EngineContext.h"
#include "ProfilerBlock.h"
#include "..\Logging\Logger.h"

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

		context->GetMessageBus()->Subscribe<BeginFrameMessage>(this, 
			[this](BeginFrameMessage message) { OnBeginFrame(); });
		context->GetMessageBus()->Subscribe<EndFrameMessage>(this,
			[this](EndFrameMessage message) { OnEndFrame(); });
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

	void Profiler::OnBeginFrame()
	{
		if (root_->IsActive())
			OnEndFrame();
		root_->Begin();
	}

	void Profiler::OnEndFrame()
	{
		EndBlock();
		root_->EndFrame();
		current_ = root_;
	}
}


