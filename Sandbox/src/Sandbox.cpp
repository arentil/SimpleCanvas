#include "SimpleCanvas.h"

class Sandbox : public sc::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

sc::Application* sc::CreateApplication()
{
	return new Sandbox();
}