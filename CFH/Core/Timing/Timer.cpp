#include "Timer.h"

#include <Windows.h>
#include <ctime>

namespace CFH
{
	static unsigned int Tick()
	{
		return (unsigned int)timeGetTime();
	}
	static long long HighResolutionTick()
	{
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return counter.QuadPart;
	}

	unsigned int Time::GetSystemTime()
	{
		return Tick();
	}
	unsigned int Time::GetTimeSinceEpoch()
	{
		return (unsigned int)time(nullptr);
	}
	const char* Time::GetTimestamp()
	{
		time_t systemTime;
		time(&systemTime);
		return ctime(&systemTime);
	}

	Timer::Timer() :
		start_(0)
	{
	}
	Timer::~Timer()
	{
	}

	void Timer::Reset()
	{
		start_ = Tick();
	}
	unsigned int Timer::GetMilliSeconds()
	{
		return (Tick() - start_);
	}

	HighResolutionTimer::HighResolutionTimer() :
		start_(0),
		frequency_(0)
	{
		LARGE_INTEGER maxFrequency;
		if (QueryPerformanceFrequency(&maxFrequency))
			frequency_ = maxFrequency.QuadPart;
	}
	HighResolutionTimer::~HighResolutionTimer()
	{
	}

	void HighResolutionTimer::Reset()
	{
		start_ = HighResolutionTick();
	}
	long long HighResolutionTimer::GetMicroSeconds()
	{
		long long current = HighResolutionTick();
		long long elapsed = current - start_;

		if (elapsed < 0)
			elapsed = 0;

		return (elapsed * 1000000LL) / frequency_;
	}
	long long HighResolutionTimer::GetFrequency()
	{
		return frequency_;
	}
}

