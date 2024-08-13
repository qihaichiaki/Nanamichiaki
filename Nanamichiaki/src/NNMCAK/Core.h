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

// ������Ժ�
#ifdef NNMCAK_ENABLE_ASSERT
	#define NNMCAK_CORE_ASSERT(x, ...) { if(!x) { NNMCAK_CORE_ERROR("����ʧ��: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NNMCAK_APP_ASSERT(x, ...) { if(!x) { NNMCAK_APP_ERROR("����ʧ��: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NNMCAK_CORE_ASSERT(x, ...)
	#define NNMCAK_APP_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)