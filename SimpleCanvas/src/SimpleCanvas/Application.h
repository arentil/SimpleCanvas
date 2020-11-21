#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerContainer.h"

namespace sc {
class SC_API Application
{
public:
	Application();
	virtual ~Application();

	void run();
	void onEvent(Event &e);
	void onWindowClose(WindowCloseEvent &e);

	void pushLayer(Layer * layer);
	void pushOverlay(Layer * overlay);

private:
	std::unique_ptr<Window> window;
	bool isRunning = false;
	LayerContainer layerContainer;
};

// to be defined in client
Application *CreateApplication();
} // namespace sc

