#pragma once

#ifdef NNMCAK_PLATFORM_WINDOWS
#ifdef NNMCAK_BUILD_DLL
	#define NNMCAK_API __declspec(dllexport)
#else
	#define NNMCAK_API __declspec(dllimport)
#endif

#else
	#error Currently NNMCAK Engine does not support other platforms!
#endif

#define BIT(x) (1 << x)