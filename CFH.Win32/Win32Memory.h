#pragma once
#include "CFH.Core\IO\Memory.h"

#include <Windows.h>

namespace CFH
{
	class Win32Memory final : public Memory
	{
	public:
		static void Setup()
		{
			Memory::Reserve = Win32Memory::Reserve;
			Memory::Free = Win32Memory::Free;
		}

		static PRESERVEFUNC(Reserve)
		{
			return VirtualAlloc(0, size,
								MEM_COMMIT | MEM_RESERVE,
								PAGE_READWRITE);
		}

		static PFREEFUNC(Free)
		{
			VirtualFree(memory, 0,
						MEM_RELEASE);
		}
	};
}

