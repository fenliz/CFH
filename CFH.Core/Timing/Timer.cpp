#include "Timer.h"
#include "CFH.Core\Timing\Time.h"

namespace CFH
{
	Timer::Timer() :
		start_(0)
	{
	}
	Timer::~Timer()
	{
	}

	void Timer::Reset()
	{
		start_ = Time::GetSystemTime();
	}
	uint32 Timer::GetMilliSeconds()
	{
		return (Time::GetSystemTime() - start_);
	}

	HighResolutionTimer::HighResolutionTimer() :
		start_(0)
	{
	}
	HighResolutionTimer::~HighResolutionTimer()
	{
	}

	void HighResolutionTimer::Reset()
	{
		start_ = Time::GetHighResSystemTime();
	}
	int64 HighResolutionTimer::GetMicroSeconds()
	{
		int64 current = Time::GetHighResSystemTime();
		int64 elapsed = current - start_;

		if (elapsed < 0)
			elapsed = 0;

		return (elapsed * (int64)1000000) / Time::GetHighResFrequency();
	}
}