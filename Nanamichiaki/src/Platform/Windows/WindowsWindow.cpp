#include "NNMCAKpch.h"
#include "WindowsWindow.h"

#include "NNMCAK/Events/ApplicationEvent.h"
#include "NNMCAK/Events/KeyEvent.h"
#include "NNMCAK/Events/MouseEvent.h"

#include "glad/glad.h"

namespace NNMCAK
{
	static bool s_GLFWInitialized = false;

	static void GLFWError(int error_code, const char* description)
	{
		NNMCAK_CORE_ERROR("glfw错误 ({0}) 描述: {1}", error_code, description);
	}

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
			glfwSetErrorCallback(GLFWError);
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height),
									m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NNMCAK_CORE_ASSERT(status, "Failed to initialize Glad!");

		// 设置用户数据
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// 窗口变化
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = static_cast<unsigned int>(width);
			data->Height = static_cast<unsigned int>(height);
			WindowResizeEvent event(data->Width, data->Height);
			
			data->EventCallback(event);
		});

		// 窗口关闭
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;

			data->EventCallback(event);
		});

		// 键盘按钮
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data->EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data->EventCallback(event);
					break;
				}
			}

		});

		// 鼠标按键  
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data->EventCallback(event);
					break;
				}
			}

		});

		// 鼠标滚动
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			data->EventCallback(event);
		});

		// 鼠标移动
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			data->EventCallback(event);
		});
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