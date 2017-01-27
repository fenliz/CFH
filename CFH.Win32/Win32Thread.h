#pragma once
#include "CFH.Core\Threading\Thread.h"

namespace CFH
{
	class Win32Thread
	{
	public:
		static void Setup()
		{
			Thread::GetThreadId = Win32Thread::GetThreadId;
			Thread::SetAsMainThread();
		}

		static PGETTHREADID(GetThreadId)
		{
			return GetCurrentThreadId();
		}
	};
}