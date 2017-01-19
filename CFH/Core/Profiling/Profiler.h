#pragma once
#include "Core\Threading\SharedMutex.h"

namespace CFH
{
	class EngineContext;
	class ProfilerBlock;

	// A tool for measuring the time of specific blocks of code.
	class Profiler
	{
	public:
		Profiler(EngineContext* context);
		~Profiler();

		void BeginBlock(const char* name);
		void EndBlock();

		void BeginInterval();

		const ProfilerBlock* GetCurrentBlock() const;
		const ProfilerBlock* GetRootBlock() const;

		Profiler* GetInstance() const;

		float GetFrameTime();

	private:
		static Profiler* instance_;
		ProfilerBlock* root_;
		ProfilerBlock* current_;
		unsigned int intervalFrames_;

		void OnBeginFrame();
		void OnEndFrame();
	};

	class AutoProfileBlock
	{
	public:
		AutoProfileBlock(Profiler* profiler, const char* name) :
			profiler_(profiler)
		{
			if (profiler_)
				profiler_->BeginBlock(name);
		}

		~AutoProfileBlock()
		{
			if (profiler_)
				profiler_->EndBlock();
		}

	private:
		Profiler* profiler_;
	};

	// Convenience macro for starting a local block with a specific name.
#define PROFILE(name) \
	AutoProfileBlock profile_&&name (Profiler::GetInstance(), #name)
}

