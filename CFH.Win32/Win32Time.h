#pragma once
#include "CFH.Core\Timing\Time.h"

#include <Windows.h>
#include <ctime>

namespace CFH
{
	class Win32Time
	{
	public:
		static void Setup()
		{
			Time::GetSystemTime = Win32Time::GetSystemTime;
			Time::GetTimeSinceEpoch = Win32Time::GetTimeSinceEpoch;

			Time::GetHighResSystemTime = Win32Time::GetHighResSystemTime;
			Time::GetHighResFrequency = Win32Time::GetHighResFrequency;

			Time::GetTimestamp = Win32Time::GetTimestamp;
		}

		static PGETTIMEFUNC(GetSystemTime)
		{
			return (uint32)timeGetTime();
		}

		static PGETTIMEFUNC(GetTimeSinceEpoch)
		{
			return (uint32)time(nullptr);
		}

		static PGETUTIMEFUNC(GetHighResSystemTime)
		{
			LARGE_INTEGER counter;
			QueryPerformanceCounter(&counter);
			return counter.QuadPart;
		}

		static PGETUTIMEFUNC(GetHighResFrequency)
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			return frequency.QuadPart;
		}

		static PGETTIMESTAMPFUNC(GetTimestamp)
		{
			char timestamp[26] = {};
			time_t t;
			time(&t);
			ctime_s(timestamp, 26 * sizeof(char), &t);

			// Remove \n
			timestamp[24] = '\0';
			return std::string(timestamp);
		}
	};
}