#include "Memory.h"
#include "CFH.Core\CFH.h"

#define MEMORY_NOT_IMPLEMENTED "Memory allocation is not implemented on this platform."

namespace CFH
{
	PRESERVEFUNC(ReserveStub) { LOG_ERROR(MEMORY_NOT_IMPLEMENTED); return nullptr; }
	RESERVEFUNC* Memory::Reserve = ReserveStub;

	PFREEFUNC(FreeStub) { LOG_ERROR(MEMORY_NOT_IMPLEMENTED); }
	FREEFUNC* Memory::Free = FreeStub;
}