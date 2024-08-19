#include "Nanamichiaki.h"

template<> struct fmt::formatter<NNMCAK::Event> : ostream_formatter {};

class ExampleLayer : public NNMCAK::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}
	void OnUpdate() override
	{
		NNMCAK_APP_INFO("ExampleLayer±»¸üÐÂ...");
	}

	void OnEvent(NNMCAK::Event& e) override
	{
		NNMCAK_APP_INFO("{0}", e);
	}
};

class Sandbox : public NNMCAK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}

	~Sandbox()
	{
	}
};

NNMCAK::Application* NNMCAK::CreateApplication()
{
	return new Sandbox();
}