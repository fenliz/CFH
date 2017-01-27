#pragma once
#include "CFH.Core\Types.h"

#include <string>

#define PGETTIMEFUNC(name) uint32 name()
typedef PGETTIMEFUNC(GETTIMEFUNC);

#define PGETUTIMEFUNC(name) int64 name()
typedef PGETUTIMEFUNC(GETUTIMEFUNC);

#define PGETTIMESTAMPFUNC(name) std::string name()
typedef PGETTIMESTAMPFUNC(GETTIMESTAMPFUNC);

namespace CFH
{
	class CFHCORE_API Time
	{
	public:
		static GETTIMEFUNC* GetSystemTime;
		static GETTIMEFUNC* GetTimeSinceEpoch;

		static GETUTIMEFUNC* GetHighResSystemTime;
		static GETUTIMEFUNC* GetHighResFrequency;

		static GETTIMESTAMPFUNC* GetTimestamp;
	};
}

