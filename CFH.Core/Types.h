#pragma once

#define KILOBYTES(x) (x * 1024)
#define MEGABYTES(x) (Kilobytes(x) * 1024)
#define GIGABYTES(x) (Megabytes(x) * 1024)

#define localPersist	static
#define globalVariable	static

#if _DEBUG
#include <Windows.h>
#define ASSERT(x) if (!x) DebugBreak()
#else
#define ASSERT(x)
#endif

#define ArrayCount(x) (sizeof(x) / sizeof(x[0]))

#include <stdint.h>

typedef int32_t		bool32;

typedef int8_t		int8;
typedef int16_t		int16;
typedef int32_t		int32;
typedef int64_t		int64;

typedef uint8_t		uint8;
typedef uint16_t	uint16;
typedef uint32_t	uint32;
typedef uint64_t	uint64;

typedef float		real32;
typedef double		real64;

#define CFH_EXPORT __declspec(dllexport)
#define CFH_IMPORT __declspec(dllimport)

#ifdef CFHCORE_EXPORTS
#define CFHCORE_API CFH_EXPORT
#else
#define CFHCORE_API CFH_IMPORT
#endif

#ifdef CFHWIN32_EXPORTS
#define CFHWIN32_API CFH_EXPORT
#else
#define CFHWIN32_API CFH_IMPORT
#endif
