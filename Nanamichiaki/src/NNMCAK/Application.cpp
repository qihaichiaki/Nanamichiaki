#include "Application.h"

#include "NNMCAK/Events/ApplicationEvent.h"
#include "NNMCAK/Log.h"
#include <iostream>


template<> struct fmt::formatter<NNMCAK::WindowResizeEvent> : ostream_formatter {};

namespace NNMCAK
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{

		WindowResizeEvent windowResizeEvent(1200, 900);
		//std::cout << windowResizeEvent << std::endl;
		NNMCAK_APP_TRACE(windowResizeEvent);
		if (!windowResizeEvent.IsInCategory(EventCategoryMouse))
		{
			NNMCAK_APP_WARN("并不是鼠标事件类型");
		}

		while (true);
	}
}