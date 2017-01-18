#pragma once

#ifdef CFH_EXPORTS
#define CFH_API __declspec(dllexport)
#else
#define CFH_API __declspec(dllimport)
#endif

#if _DEBUG
#define ASSERT(x) \
	if (!x) DebugBreak()
#else
#define ASSERT(x)
#endif