#include "Application.h"

#include <glad/glad.h>

#include "Events/KeyEvent.h"

namespace sc {
Application::Application()
{
	window = std::unique_ptr<Window>(Window::create());
	isRunning = true;
	window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));


	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);


	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	unsigned int indices[3] = { 0, 1, 2	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position + 0.5;
			gl_Position = vec4(a_Position + 0.5, 1.0);
		}
	)";

	std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 a_color;

		in vec3 v_Position;

		void main()
		{
			a_color = vec4(v_Position * 0.5 + 0.5, 1.0);
		}
	)";


	shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);

	// vertex array
	// vertex buffer
	// idnex buffer
	// shader -- after
}

Application::~Application()
{
}

void Application::run()
{
	while (isRunning)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->bind();

		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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