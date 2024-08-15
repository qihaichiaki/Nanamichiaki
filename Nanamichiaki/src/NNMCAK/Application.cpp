#include "NNMCAKpch.h"
#include "Application.h"

#include "NNMCAK/Log.h"
#include "gl/GL.h"


template<> struct fmt::formatter<NNMCAK::Event> : ostream_formatter {};

namespace NNMCAK
{

#define EVENT_BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EVENT_BIND_FN(OnEvent));
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(EVENT_BIND_FN(OnWindowClose));

		NNMCAK_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}