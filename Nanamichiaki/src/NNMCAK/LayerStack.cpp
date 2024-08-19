#include "NNMCAKpch.h"
#include "LayerStack.h"

namespace NNMCAK
{
	LayerStack::LayerStack()
	{
		m_LayersInsert = m_Layers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (auto& item : m_Layers) delete item;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayersInsert = m_Layers.emplace(m_LayersInsert, layer);
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayersInsert--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}