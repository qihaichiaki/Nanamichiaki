#include "Nanamichiaki.h"

class Sandbox : public NNMCAK::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

NNMCAK::Application* NNMCAK::CreateApplication()
{
	return new Sandbox();
}