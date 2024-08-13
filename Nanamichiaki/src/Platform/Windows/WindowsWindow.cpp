#include "NNMCAKpch.h"
#include "WindowsWindow.h"

namespace NNMCAK
{
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& prpos)
	{
		Init(prpos);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
			m_Data.VSync = true;
		}
		else
		{
			glfwSwapInterval(0);
			m_Data.VSync = false;
		}
	}
	void WindowsWindow::Init(const WindowProps& prpos)
	{
		m_Data.Title = prpos.Title;
		m_Data.Width = prpos.Width;
		m_Data.Height = prpos.Height;

		NNMCAK_CORE_INFO("创建窗口L: {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			NNMCAK_CORE_ASSERT(success, "未能成功初始化glfwInit!");
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height),
									m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
}