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

		// 附加
		virtual void OnAttach() {}
		// 分离
		virtual void OnDetach() {}
		// 更新
		virtual void OnUpdate() {}
		// 响应事件
		virtual void OnEvent(Event&) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}