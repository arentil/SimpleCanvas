#include "Application.h"

#include "Events/KeyEvent.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

namespace sc {
Application::Application()
{
	window = std::unique_ptr<Window>(Window::create());
	isRunning = true;
	window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

	_vertexArray.reset(VertexArray::create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	std::shared_ptr<VertexBuffer>vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position"},
		{ ShaderDataType::Float4, "a_Color"}
	};

	vertexBuffer->setLayout(layout);
	_vertexArray->addVertexBuffer(vertexBuffer);
	
	
	unsigned int indices[3] = { 0, 1, 2	};
	std::shared_ptr<IndexBuffer>indexBuffer = IndexBuffer::create(indices, 3);
	_vertexArray->setIndexBuffer(indexBuffer);

	std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec3 v_Position;
		out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 a_color;
		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			a_color = v_Color;
		}
	)";

	_vertexArray2.reset(VertexArray::create());

	float vertices2[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	std::shared_ptr<VertexBuffer> vertexBuffer2 = VertexBuffer::create(vertices2, sizeof(vertices2));

	BufferLayout layout2 = {
		{ ShaderDataType::Float3, "a_Position"},
	};

	vertexBuffer2->setLayout(layout2);
	_vertexArray2->addVertexBuffer(vertexBuffer2);
	
	
	unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<IndexBuffer> indexBuffer2 = IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
	_vertexArray2->setIndexBuffer(indexBuffer2);

	std::string vertexSrc2 = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;


		void main()
		{
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentSrc2 = R"(
		#version 330 core

		layout(location = 0) out vec4 a_color;

		void main()
		{
			a_color = vec4(0.2, 0.3, 0.8, 1.0);
		}
	)";

	shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
	shader2 = std::make_unique<Shader>(vertexSrc2, fragmentSrc2);
}

Application::~Application()
{}

void Application::run()
{
	while (isRunning)
	{
		RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		RenderCommand::clear();

		Renderer::beginScene();

			shader2->bind();
			Renderer::submit(_vertexArray2);

			shader->bind();
			Renderer::submit(_vertexArray);

		Renderer::endScene();

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