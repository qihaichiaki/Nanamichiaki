#pragma once

#include <stdio.h>

#ifdef NNMCAK_PLATFORM_WINDOWS

extern NNMCAK::Application* NNMCAK::CreateApplication();

int main()
{
	NNMCAK::Log::Init();
	printf("Wellcome to Nanamichiaki Engine...\n");
	auto app = NNMCAK::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif