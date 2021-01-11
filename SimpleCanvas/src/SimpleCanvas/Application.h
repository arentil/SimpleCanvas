#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerContainer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace sc {
class Application
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

	std::shared_ptr<Shader> shader;
	std::shared_ptr<VertexArray> _vertexArray;

	std::shared_ptr<Shader> shader2;
	std::shared_ptr<VertexArray> _vertexArray2;
};

// to be defined in client
Application *CreateApplication();
} // namespace sc

