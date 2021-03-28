#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerContainer.h"

namespace sc 
{
class Application
{
public:
	Application();
	virtual ~Application();

	void run();
	void onEvent(Event &event);
	void onWindowClose(WindowCloseEvent &event);
	void onWindowResize(WindowResizeEvent &event);

	void pushLayer(Layer * layer);
	void pushOverlay(Layer * overlay);

private:
	WindowPtr window;
	bool _isRunning = false;
	bool _windowMinimized = false;
	LayerContainer layerContainer;
};

// to be defined in client
Application *CreateApplication();
} // namespace sc

