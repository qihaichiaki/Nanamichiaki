#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace NNMCAK
{
	class NNMCAK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}



// 定义一些日志宏方便使用。注意必须优先调用Init才能使用
// Core 引擎
#define NNMCAK_CORE_TRACE(...)	::NNMCAK::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NNMCAK_CORE_INFO(...)	::NNMCAK::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NNMCAK_CORE_WARN(...)	::NNMCAK::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NNMCAK_CORE_ERROR(...)	::NNMCAK::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NNMCAK_CORE_FATAL(...)	::NNMCAK::Log::GetCoreLogger()->critical(__VA_ARGS__)

// App 应用
#define NNMCAK_APP_TRACE(...)	::NNMCAK::Log::GetAppLogger()->trace(__VA_ARGS__)
#define NNMCAK_APP_INFO(...)	::NNMCAK::Log::GetAppLogger()->info(__VA_ARGS__)
#define NNMCAK_APP_WARN(...)	::NNMCAK::Log::GetAppLogger()->warn(__VA_ARGS__)
#define NNMCAK_APP_ERROR(...)	::NNMCAK::Log::GetAppLogger()->error(__VA_ARGS__)
#define NNMCAK_APP_FATAL(...)	::NNMCAK::Log::GetAppLogger()->critical(__VA_ARGS__)
