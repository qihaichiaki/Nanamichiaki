#pragma once

#include "Core.h"

#include "NNMCAK/Events/Event.h"

namespace NNMCAK
{
	class NNMCAK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}