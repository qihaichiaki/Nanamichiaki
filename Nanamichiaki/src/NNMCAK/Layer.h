#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace NNMCAK
{
	class NNMCAK_API Layer
	{
	public:
		Layer(const std::string name);
		virtual ~Layer();

		// ����
		virtual void OnAttach() {}
		// ����
		virtual void OnDetach() {}
		// ����
		virtual void OnUpdate() {}
		// ��Ӧ�¼�
		virtual void OnEvent(Event&) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}