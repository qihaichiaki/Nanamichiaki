#pragma once

#include "NNMCAK/Core.h"
#include "NNMCAK/Events/Event.h"

namespace NNMCAK
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps()
			: Title("NNMCAK Engine"), Width(1280), Height(720)
		{}
	};

	// �������Window�࣬ȫƽ̨ͨ��
	class NNMCAK_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		// �����GLFW������������ѯ�����¼�..
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// �����¼��ص�
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		// ���ô�ֱͬ����
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}