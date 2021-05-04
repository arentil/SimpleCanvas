#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Canvas.h"

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

	void initCanvas(Canvas *canvas);

private:
	WindowPtr window;
	bool _isRunning = false;
	bool _windowMinimized = false;
	Canvas *_currentCanvas;
};

// to be defined in client
Application *CreateApplication();
} // namespace sc

