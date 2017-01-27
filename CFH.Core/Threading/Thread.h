#pragma once
#include "CFH.Core\Types.h"

#define PGETTHREADID(name) uint32 name()
typedef PGETTHREADID(GETTHREADIDFUNC);

namespace CFH
{
	class CFHCORE_API Thread
	{
	public:
		static GETTHREADIDFUNC* GetThreadId;

		static void SetAsMainThread()
		{
			mainThread_ = GetThreadId();
		}

		static bool32 IsMainThread()
		{
			return mainThread_ == GetThreadId();
		}

	private:
		static uint32 mainThread_;
	};
}