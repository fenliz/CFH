#include "Time.h"
#include "CFH.Core\CFH.h"

#define TIME_NOT_IMPLEMENTED "Time is not implemented on this platform."

namespace CFH
{
	PGETTIMEFUNC(GetTimeStub) { LOG_ERROR(TIME_NOT_IMPLEMENTED); return 0; }
	GETTIMEFUNC* Time::GetSystemTime = GetTimeStub;
	GETTIMEFUNC* Time::GetTimeSinceEpoch = GetTimeStub;

	PGETUTIMEFUNC(GetUTimeStub) { LOG_ERROR(TIME_NOT_IMPLEMENTED); return 0; }
	GETUTIMEFUNC* Time::GetHighResSystemTime = GetUTimeStub;
	GETUTIMEFUNC* Time::GetHighResFrequency = GetUTimeStub;

	PGETTIMESTAMPFUNC(GetTimestampStub) { LOG_ERROR(TIME_NOT_IMPLEMENTED); return nullptr; }
	GETTIMESTAMPFUNC* Time::GetTimestamp = GetTimestampStub;
}

