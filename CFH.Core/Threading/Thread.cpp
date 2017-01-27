#include "Thread.h"
#include "CFH.Core\CFH.h"

#define THREAD_NOT_IMPLEMENTED "Threading is not implemented on this platform."

namespace CFH
{
	uint32 Thread::mainThread_ = 0;

	PGETTHREADID(GetThreadIdStub) { LOG_ERROR(THREAD_NOT_IMPLEMENTED); return 0; }
	GETTHREADIDFUNC* Thread::GetThreadId = GetThreadIdStub;
}