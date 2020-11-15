#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace sc {
class SC_API Application
{
public:
	Application();
	virtual ~Application();

	void run();
	void onEvent(Event &e);
	bool onWindowClose(WindowCloseEvent &e);

private:
	std::unique_ptr<Window> window;
	bool isRunning = false;
};

// to be defined in client
Application *CreateApplication();
} // namespace sc

