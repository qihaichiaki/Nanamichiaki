#include "NNMCAKpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace NNMCAK
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	// 初始化日志
	void Log::Init()
	{
		/* 
		* _设置日志格式_
		* %^ ... %$ 使用颜色
		* %T 为当前时间显示
		* %n为当前控制台名字
		* %v为日志内容
		* 详情：https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		*/
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("NNMCAK");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_AppLogger = spdlog::stdout_color_mt("APP");
		s_AppLogger->set_level(spdlog::level::trace);
	}
}