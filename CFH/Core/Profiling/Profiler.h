#pragma once
#include "..\Threading\SharedMutex.h"

namespace CFH
{
	class EngineContext;
	class ProfilerBlock;

	class Profiler
	{
	public:
		Profiler(EngineContext* context);
		~Profiler();

		void BeginBlock(const char* name);
		void EndBlock();
		void BeginInterval();

		const ProfilerBlock* GetCurrentBlock() const;
		const ProfilerBlock* GetRootBlokc() const;

		Profiler* GetInstance()
		{
			return instance_;
		}

	private:
		static Profiler* instance_;
		ProfilerBlock* root_;
		ProfilerBlock* current_;

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

#define PROFILE(name) \
	AutoProfileBlock profile_&&name (Profiler::GetInstance(), #name)
}

