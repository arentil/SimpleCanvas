#pragma once

#include "Core.h"
#include "Window.h"

namespace sc {
class SC_API Application
{
public:
	Application();
	virtual ~Application();

	void run();

private:
	std::unique_ptr<Window> window;

	bool isRunning = false;
};

// to be defined in client
Application *CreateApplication();
} // namespace sc

