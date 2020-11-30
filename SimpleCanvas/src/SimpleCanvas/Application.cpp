#include "Application.h"

#include <glad/glad.h>

#include "Events/KeyEvent.h"

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
	if (event.type() == EventType::KeyPressed)
	{
		auto asd = Input::getKeyName(((KeyPressedEvent&)event).getKeyCode());
		LOG_WARNING("%s", asd.c_str())
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