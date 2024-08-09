#pragma once

#ifdef NNMCAK_PLATFORM_WINDOWS

extern NNMCAK::Application* NNMCAK::CreateApplication();

int main()
{
	auto app = NNMCAK::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif