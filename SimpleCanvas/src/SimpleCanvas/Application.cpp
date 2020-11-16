#include "Application.h"

#include "Logger.h"

#include <GLFW/glfw3.h>

namespace sc {
Application::Application()
{
	window = std::unique_ptr<Window>(Window::create());
	isRunning = true;
	window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
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

void Application::onEvent(Event &event)
{
	EventDispatcher dispatcher;
	dispatcher.subscribe(this, &Application::onWindowClose);



	dispatcher.dispatch(event);
	LOG_INFO(event.name());
}

void Application::onWindowClose(WindowCloseEvent &e)
{
	isRunning = false;
}

} // namespace sc