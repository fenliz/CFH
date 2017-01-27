#pragma once
#include "CFH.Core\Timing\Timer.h"

#include <vector>

namespace CFH
{
	// Used for measuring time within a specific timeframe.
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

		ProfilerBlock* GetChild(const char* name);
		ProfilerBlock* GetParent() const;

		int64 GetTime() const;
		int64 GetFrameTime() const;
		
	private:
		const char* name_;
		HighResolutionTimer timer_;

		ProfilerBlock* parent_;
		std::vector<ProfilerBlock*> children_;

		int64 time_;
		int64 maxTime_;
		uint32 count_;

		int64 frameTime_;
		int64 frameMaxTime_;
		uint32 frameCount_;

		int64 intervalTime_;
		int64 intervalMaxTime_;
		uint32 intervalCount_;

		int64 totalTime_;
		int64 totalMaxTime_;
		uint32 totalCount_;
	};
}