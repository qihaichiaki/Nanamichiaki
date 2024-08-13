#include "NNMCAKpch.h"
#include "Application.h"

#include "NNMCAK/Events/ApplicationEvent.h"
#include "NNMCAK/Log.h"
#include "gl/GL.h"


template<> struct fmt::formatter<NNMCAK::WindowResizeEvent> : ostream_formatter {};

namespace NNMCAK
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent windowResizeEvent(1200, 900);
		NNMCAK_APP_TRACE(windowResizeEvent);
		if (!windowResizeEvent.IsInCategory(EventCategoryMouse))
		{
			NNMCAK_APP_WARN("并不是鼠标事件类型");
		}

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}