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
		EventCategoryApplication = BIT(0),		// Ӧ�����		   1
		EventCategoryInput		 = BIT(1),		// �������		  10
		EventCategoryKeyboard    = BIT(2),		// �������		 100
		EventCategoryMouse		 = BIT(3),		// ������		1000
		EventCategoryMouseButton = BIT(4)		// ��갴ť��� 10000
	};

	// ����һЩEvent��������д�麯���ĺ꣬��Ϊ��д��Щ�ǳ��й�ͬ��

	// �¼�������д��
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								   virtual EventType GetEventType() const override { return GetStaticType(); } \
								   virtual const char* GetName() const override { return #type; }
	// �¼������д��
	#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategory() const override { return category; }

	// �¼��Ļ���
	class NNMCAK_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;	// �����¼�����
		virtual const char* GetName() const	   = 0;	// �����¼�����
		virtual int GetEventCategory() const   = 0; // �����¼����

		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetEventCategory() & category;
		}
		
	protected:
		bool m_Handled = false;  // ����¼��Ƿ񱻴�����
	};

	// �¼�������
	class NNMCAK_API EventDispatcher
	{
		template<typename T>  // T����ΪEvent�Ļ���
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{}

		// ���Ⱥ���
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*((T*)(&m_Event)));  // ��������ת��Ϊ���������ú���
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