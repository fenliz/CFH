#pragma once

#define CFH_EXPORT __declspec(dllexport)

#ifdef CFH_EXPORTS
#define CFH_API __declspec(dllexport)
#else
#define CFH_API __declspec(dllimport)
#endif

#if _DEBUG
#include <Windows.h>
#define ASSERT(x) \
	if (!x) DebugBreak()
#else
	if (!x) assert(x)
#define ASSERT(x)
#endif