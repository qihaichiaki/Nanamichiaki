#include "NNMCAKpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace NNMCAK
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	// ��ʼ����־
	void Log::Init()
	{
		/* 
		* _������־��ʽ_
		* %^ ... %$ ʹ����ɫ
		* %T Ϊ��ǰʱ����ʾ
		* %nΪ��ǰ����̨����
		* %vΪ��־����
		* ���飺https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		*/
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("NNMCAK");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_AppLogger = spdlog::stdout_color_mt("APP");
		s_AppLogger->set_level(spdlog::level::trace);
	}
}