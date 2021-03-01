#include "Application.h"

#include "Events/KeyEvent.h"
#include "Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace sc {
Application::Application()
{
	window = WindowPtr(Window::create());
	_isRunning = true;
	window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	Renderer::init();
}

Application::~Application()
{}

void Application::run()
{
	float lastFrameDeltaTime = 0.0;

	while (_isRunning)
	{
		float time = (float)glfwGetTime();
		float deltaTime = time - lastFrameDeltaTime;
		lastFrameDeltaTime = time;

		if (!_windowMinimized)
			for (Layer* layer : layerContainer)
				layer->update(deltaTime);

		window->update();
	}
}

void Application::onEvent(Event &event)
{
	EventDispatcher dispatcher;
	dispatcher.subscribe(this, &Application::onWindowClose);
	dispatcher.subscribe(this, &Application::onWindowResize);

	for (auto it = layerContainer.end(); it != layerContainer.begin(); )
	{
		(*--it)->onEvent(event);
		if (event.isHandled())
			break;
	}

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

void Application::pushLayer(Layer * layer)
{
	layerContainer.pushLayer(layer);
}

void Application::pushOverlay(Layer * overlay)
{
	layerContainer.pushOverlay(overlay);
}

} // namespace sc