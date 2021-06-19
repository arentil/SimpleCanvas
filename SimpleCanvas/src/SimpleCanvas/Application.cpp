#include "Application.h"

#include "Events/KeyEvent.h"
#include "Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace sc 
{
Application::Application()
{
	window = WindowPtr(Window::create());
	_isRunning = true;
	window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	Renderer::init();
	dispatcher.subscribe(this, &Application::onWindowClose);
	dispatcher.subscribe(this, &Application::onWindowResize);
}

Application::~Application()
{
	delete _currentCanvas;
}

void Application::run()
{
	float lastFrameDeltaTime = (float)glfwGetTime();

	while (_isRunning)
	{
		float currentTime = (float)glfwGetTime();
		float deltaTime = currentTime - lastFrameDeltaTime;
		lastFrameDeltaTime = currentTime;
		
		if (!_windowMinimized)
		{
			_currentCanvas->update(deltaTime);
		}

		window->update();
	}
}

void Application::onEvent(Event &event)
{
	_currentCanvas->onEvent(event);
	dispatcher.dispatch(event);
}

void Application::onWindowClose(WindowCloseEvent &event)
{
	_isRunning = false;
}

void Application::onWindowResize(WindowResizeEvent &event)
{
	if (event.getWidth() == 0 || event.getHeight() == 0)
		_windowMinimized = true;

	_windowMinimized = false;
	Renderer::setViewport(0, 0, event.getWidth(), event.getHeight());
}

void Application::initCanvas(Canvas *canvas) 
{
	_currentCanvas = canvas;
}
} // namespace sc