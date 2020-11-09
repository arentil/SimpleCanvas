#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Logger.h"

#include <GLFW/glfw3.h>

namespace sc {
Application::Application()
{
	window = std::unique_ptr<Window>(Window::create());
	isRunning = true;
}

Application::~Application()
{
}

void Application::run()
{
	while (isRunning)
	{
		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		window->onUpdate();
	}
}
} // namespace sc