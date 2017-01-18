#pragma once
#include "..\Timing\Timer.h"

#include <string>
#include <vector>

namespace CFH
{
	class ProfilerBlock
	{
	public:
		ProfilerBlock(ProfilerBlock* parent, const char* name);
		virtual ~ProfilerBlock();

		void Begin();
		void End();

		void EndFrame();

		void BeginInterval();

		bool IsActive() const;
		const char* GetName() const;

		ProfilerBlock* GetChild(const char* name) const;
		ProfilerBlock* GetParent() const;

		long long GetFrameTime() const { return frameTime_; }
	private:
		const char* name_;
		HighResolutionTimer timer_;

		ProfilerBlock* parent_;
		std::vector<ProfilerBlock*> children_;

		long long time_;
		long long maxTime_;
		unsigned int count_;

		long long frameTime_;
		long long frameMaxTime_;
		unsigned int frameCount_;

		long long intervalTime_;
		long long intervalMaxTime_;
		unsigned int intervalCount_;

		long long totalTime_;
		long long totalMaxTime_;
		unsigned int totalCount_;
	};
}