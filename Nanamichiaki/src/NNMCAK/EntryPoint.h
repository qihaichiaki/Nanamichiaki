#pragma once

#include <stdio.h>

#ifdef NNMCAK_PLATFORM_WINDOWS

extern NNMCAK::Application* NNMCAK::CreateApplication();

int main()
{
	NNMCAK::Log::Init();
	printf("Wellcome to Nanamichiaki Engine...\n");

	NNMCAK_CORE_TRACE("²âÊÔ³ÌÐò-trace");
	NNMCAK_CORE_INFO("²âÊÔ³ÌÐò-info");
	NNMCAK_CORE_WARN("²âÊÔ³ÌÐò-warn");
	NNMCAK_CORE_ERROR("²âÊÔ³ÌÐò-error");
	NNMCAK_CORE_FATAL("²âÊÔ³ÌÐò-fatal");

	NNMCAK_APP_TRACE("²âÊÔ³ÌÐò-trace");
	NNMCAK_APP_INFO("²âÊÔ³ÌÐò-info");
	NNMCAK_APP_WARN("²âÊÔ³ÌÐò-warn");
	NNMCAK_APP_ERROR("²âÊÔ³ÌÐò-error");
	NNMCAK_APP_FATAL("²âÊÔ³ÌÐò-fatal");

	auto app = NNMCAK::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif