#pragma once
#include "..\..\CFH.h"

namespace CFH
{
	class CFH_API Time
	{
	public:
		static unsigned int GetSystemTime();
		static unsigned int GetTimeSinceEpoch();
		static const char* GetTimestamp();
	};

	class CFH_API Timer
	{
	public:
		Timer();
		~Timer();

		void Reset();
		unsigned int GetMilliSeconds();

	protected:
		unsigned int start_;
	};

	class CFH_API HighResolutionTimer
	{
	public:
		HighResolutionTimer();
		~HighResolutionTimer();

		void Reset();
		long long GetMicroSeconds();
		long long GetFrequency();

	protected:
		long long start_;
		long long frequency_;
	};
}

