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

	// 顶层抽象Window类，全平台通用
	class NNMCAK_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		// 会更新GLFW、缓冲区会轮询输入事件..
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// 设置事件回调
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		// 设置垂直同步？
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}