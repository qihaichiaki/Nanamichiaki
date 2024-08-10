#pragma once

#include <stdio.h>

#ifdef NNMCAK_PLATFORM_WINDOWS

extern NNMCAK::Application* NNMCAK::CreateApplication();

int main()
{
	NNMCAK::Log::Init();
	printf("Wellcome to Nanamichiaki Engine...\n");

	NNMCAK_CORE_TRACE("���Գ���-trace");
	NNMCAK_CORE_INFO("���Գ���-info");
	NNMCAK_CORE_WARN("���Գ���-warn");
	NNMCAK_CORE_ERROR("���Գ���-error");
	NNMCAK_CORE_FATAL("���Գ���-fatal");

	NNMCAK_APP_TRACE("���Գ���-trace");
	NNMCAK_APP_INFO("���Գ���-info");
	NNMCAK_APP_WARN("���Գ���-warn");
	NNMCAK_APP_ERROR("���Գ���-error");
	NNMCAK_APP_FATAL("���Գ���-fatal");

	auto app = NNMCAK::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif