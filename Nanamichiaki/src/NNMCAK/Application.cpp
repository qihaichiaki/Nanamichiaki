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

			// 每个层先更新
			for (auto& layer : m_LayerStack) layer->OnUpdate();

			// 窗口更新
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_BIND_FN(OnWindowClose));

		// 层从后往前传递事件
		for (auto layerIt = m_LayerStack.end(); layerIt != m_LayerStack.begin();)
		{
			(*--layerIt)->OnEvent(e);
			if (e.m_Handled)
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}