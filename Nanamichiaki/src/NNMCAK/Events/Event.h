#pragma once

#include "NNMCAKpch.h"
#include "NNMCAK/Core.h"


namespace NNMCAK
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),		// 应用类别		   1
		EventCategoryInput		 = BIT(1),		// 输入类别		  10
		EventCategoryKeyboard    = BIT(2),		// 键盘类别		 100
		EventCategoryMouse		 = BIT(3),		// 鼠标类别		1000
		EventCategoryMouseButton = BIT(4)		// 鼠标按钮类别 10000
	};

	// 定义一些Event派生类重写虚函数的宏，因为重写这些非常有共同点

	// 事件类型重写宏
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								   virtual EventType GetEventType() const override { return GetStaticType(); } \
								   virtual const char* GetName() const override { return #type; }
	// 事件类别重写宏
	#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategory() const override { return category; }

	// 事件的基类
	class NNMCAK_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;	// 返回事件类型
		virtual const char* GetName() const	   = 0;	// 返回事件名字
		virtual int GetEventCategory() const   = 0; // 返回事件类别

		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetEventCategory() & category;
		}
		
	protected:
		bool m_Handled = false;  // 检查事件是否被处理了
	};

	// 事件调度器
	class NNMCAK_API EventDispatcher
	{
		template<typename T>  // T必须为Event的基类
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{}

		// 调度函数
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*((T*)(&m_Event)));  // 基类类型转换为派生类后调用函数
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}