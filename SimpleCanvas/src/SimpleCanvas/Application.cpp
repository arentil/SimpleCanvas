#include "Application.h"

#include "Events/KeyEvent.h"

namespace sc {
Application::Application()
{
	window = std::unique_ptr<Window>(Window::create());
	isRunning = true;
	window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
}

Application::~Application()
{}

void Application::run()
{
	while (isRunning)
	{
		for (Layer* layer : layerContainer)
			layer->update();

		window->update();
	}
}

void Application::onEvent(Event &event)
{
	EventDispatcher dispatcher;
	dispatcher.subscribe(this, &Application::onWindowClose);

	for (auto it = layerContainer.end(); it != layerContainer.begin(); )
	{
		(*--it)->onEvent(event);
		if (event.isHandled())
			break;
	}

	dispatcher.dispatch(event);
	LOG_ERROR("%s", event.name().c_str());
}

void Application::onWindowClose(WindowCloseEvent &e)
{
	isRunning = false;
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