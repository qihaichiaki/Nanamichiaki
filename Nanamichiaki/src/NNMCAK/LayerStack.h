#pragma once

#include "Core.h"
#include "Layer.h"

namespace NNMCAK
{
	class NNMCAK_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer*);
		void PushOverlay(Layer*);
		void PopLayer(Layer*);
		void PopOverlay(Layer*);

		// µü´úÆ÷Ïà¹Ø
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayersInsert;
	};
}
