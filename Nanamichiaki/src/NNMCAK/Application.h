#pragma once

#include "Core.h"

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