#include "Application.h"

#include "Events\ApplicationEvent.h"
#include "Logger.h"

namespace sc {
Application::Application()
{
}


Application::~Application()
{
}

void Application::run()
{
	WindowResizeEvent e(1280, 720);
	LOG_TEXT(e.ToString());
	while (true);
}
}