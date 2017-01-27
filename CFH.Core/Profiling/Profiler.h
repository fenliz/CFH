#pragma once
#include "ProfilerBlock.h"

namespace CFH
{
	// Handles measuring nested blocks of code
	class CFHCORE_API Profiler
	{
	public:
		Profiler();
		~Profiler();

		void BeginBlock(const char* name);
		void EndBlock();

		void BeginInterval();

		const ProfilerBlock* GetCurrentBlock() const;
		const ProfilerBlock* GetRootBlock() const;

		real32 GetFrameTime() const;

		static Profiler* GetInstance();

	private:
		Profiler(const Profiler&) = delete;
		Profiler& operator=(const Profiler&) = delete;

		void OnBeginFrame();
		void OnEndFrame();

		ProfilerBlock* root_;
		ProfilerBlock* current_;
		int32 intervalFrames_;
	};

	class CFHCORE_API AutoProfilerBlock
	{
	public:
		AutoProfilerBlock(Profiler* profiler, const char* name) :
			profiler_(profiler)
		{
			ASSERT(profiler_);
			profiler_->BeginBlock(name);
		}
		~AutoProfilerBlock()
		{
			ASSERT(profiler_);
			profiler_->EndBlock();
		}

	private:
		Profiler* profiler_;
	};

#define PROFILE(name) \
	AutoProfilerBlock profile_##name(Profiler::GetInstance(), #name)
}