#pragma once

#include "Core.h"
#include "Platform/Windows/WindowsWindow.h"


namespace NNMCAK
{
	class NNMCAK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}