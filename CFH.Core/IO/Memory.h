#pragma once
#include "CFH.Core\Types.h"

#define PRESERVEFUNC(name) void* name(uint32 size)
typedef PRESERVEFUNC(RESERVEFUNC);

#define PFREEFUNC(name) void name(void* memory)
typedef PFREEFUNC(FREEFUNC);

namespace CFH
{
	class CFHCORE_API Memory
	{
	public:
		static RESERVEFUNC* Reserve;
		static FREEFUNC* Free;
	};
}