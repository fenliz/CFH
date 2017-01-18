#pragma once
#include <Windows.h>

namespace CFH
{
	class Thread
	{
	public:
		static void SetAsMainThread()
		{
			mainThread_ = GetThreadId();
		}

		static unsigned int GetThreadId()
		{
			return GetCurrentThreadId();
		}

		static bool IsMainThread()
		{
			return mainThread_ == GetThreadId();
		}

	private:
		static unsigned int mainThread_;
	};
}