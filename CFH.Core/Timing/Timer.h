#pragma once
#include "CFH.Core\Types.h"

namespace CFH
{
	// A low resolution timer (milliseconds).
	class CFHCORE_API Timer
	{
	public:
		Timer();
		~Timer();

		void Reset();
		uint32 GetMilliSeconds();

	protected:
		uint32 start_;
	};

	// A high resolution timer (microseconds) for when more granularity is needed.
	class CFHCORE_API HighResolutionTimer
	{
	public:
		HighResolutionTimer();
		~HighResolutionTimer();

		void Reset();
		int64 GetMicroSeconds();

	protected:
		int64 start_;
	};
}