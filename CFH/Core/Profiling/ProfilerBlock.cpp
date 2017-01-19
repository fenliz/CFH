#include "ProfilerBlock.h"

namespace CFH
{
	ProfilerBlock::ProfilerBlock(ProfilerBlock* parent, const char* name) :
		name_(name),
		parent_(parent),
		time_(0),
		maxTime_(0),
		count_(0),
		frameTime_(0),
		frameMaxTime_(0),
		frameCount_(0),
		intervalTime_(0),
		intervalMaxTime_(0),
		intervalCount_(0),
		totalTime_(0),
		totalMaxTime_(0),
		totalCount_(0)
	{
	}
	ProfilerBlock::~ProfilerBlock()
	{
		for (auto child : children_)
			delete child;
	}

	void ProfilerBlock::Begin()
	{
		timer_.Reset();
		count_++;
	}

	void ProfilerBlock::End()
	{
		long long blockTime = timer_.GetMicroSeconds();
		if (maxTime_ < blockTime)
			maxTime_ = blockTime;
		time_ += blockTime;
	}

	void ProfilerBlock::EndFrame()
	{
		frameTime_ = time_;
		frameMaxTime_ = maxTime_;
		frameCount_ = count_;

		intervalTime_ += time_;
		if (intervalMaxTime_ < maxTime_)
			intervalMaxTime_ = maxTime_;
		intervalCount_ = count_;

		totalTime_ += time_;
		if (totalMaxTime_ < maxTime_)
			totalMaxTime_ = maxTime_;
		totalCount_ += count_;

		time_ = 0;
		maxTime_ = 0;
		count_ = 0;

		for (auto child : children_)
			child->EndFrame();
	}

	void ProfilerBlock::BeginInterval()
	{
		intervalTime_ = 0;
		intervalMaxTime_ = 0;
		intervalCount_ = 0;

		for (auto child : children_)
			child->BeginInterval();
	}

	bool ProfilerBlock::IsActive() const
	{
		return count_ != 0;
	}
	const char* ProfilerBlock::GetName() const
	{
		return name_;
	}

	ProfilerBlock* ProfilerBlock::GetChild(const char* name) const
	{
		for (auto child : children_)
		{
			if (child->GetName() == name)
				return child;
		}
		return nullptr;
	}

	ProfilerBlock* ProfilerBlock::GetParent() const
	{
		return parent_;
	}
}

