#pragma once

#include "Core.h"
#include "Platform/Windows/WindowsWindow.h"
#include "NNMCAK/Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace NNMCAK
{
	class NNMCAK_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void PushLayer(Layer*);
		void PushOverlay(Layer*);

		void OnEvent(Event&);
		bool OnWindowClose(WindowCloseEvent&);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}