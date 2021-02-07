#include "SimpleCanvas.h"

#include <memory>

class ExampleLayer : public sc::Layer
{
public:
	ExampleLayer()
	: Layer("Example")
	, _camera(-1.6f, 1.6f, -0.9f, 0.9f)
	, _cameraPos(0, 0, 0)
	{
		_vertexArray.reset(sc::VertexArray::create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		auto vertexBuffer = sc::VertexBuffer::create(vertices, sizeof(vertices));

		sc::BufferLayout layout = {
			{ sc::ShaderDataType::Float3, "a_Position"},
			{ sc::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->setLayout(layout);
		_vertexArray->addVertexBuffer(vertexBuffer);
		
		
		unsigned int indices[3] = { 0, 1, 2	};
		auto indexBuffer = sc::IndexBuffer::create(indices, 3);
		_vertexArray->setIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		_vertexArray2.reset(sc::VertexArray::create());

		float vertices2[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		auto vertexBuffer2 =sc::VertexBuffer::create(vertices2, sizeof(vertices2));

		sc::BufferLayout layout2 = {
			{ sc::ShaderDataType::Float3, "a_Position"}
		};

		vertexBuffer2->setLayout(layout2);
		_vertexArray2->addVertexBuffer(vertexBuffer2);
		
		
		unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<sc::IndexBuffer> indexBuffer2 = sc::IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
		_vertexArray2->setIndexBuffer(indexBuffer2);

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		shader = std::make_unique<sc::Shader>(vertexSrc, fragmentSrc);
		shader2 = std::make_unique<sc::Shader>(vertexSrc2, fragmentSrc2);
	}

	void update(float deltaTime) override
	{
		if (sc::Input::isKeyPressed(sc::KEY_LEFT))
		{
			_cameraPos.x -= _cameraMoveSpeed * deltaTime;
		}
		else if (sc::Input::isKeyPressed(sc::KEY_RIGHT))
		{
			_cameraPos.x += _cameraMoveSpeed * deltaTime;
		}

		if (sc::Input::isKeyPressed(sc::KEY_UP))
		{
			_cameraPos.y += _cameraMoveSpeed * deltaTime;
		}
		else if (sc::Input::isKeyPressed(sc::KEY_DOWN))
		{
			_cameraPos.y -= _cameraMoveSpeed * deltaTime;
		}

		if (sc::Input::isKeyPressed(sc::KEY_A))
		{
			_cameraRot += _cameraRotSpeed * deltaTime;
		}
		else if (sc::Input::isKeyPressed(sc::KEY_D))
		{
			_cameraRot -= _cameraRotSpeed * deltaTime;
		}

		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();

		_camera.setPosition(_cameraPos); // move camera right and up
		_camera.setRotation(_cameraRot); // move camera right and up
		

		sc::Renderer::beginScene(_camera);

			sc::Renderer::submit(_vertexArray2, shader2);
			sc::Renderer::submit(_vertexArray, shader);

		sc::Renderer::endScene();
	}

	void onEvent(sc::Event &event) override
	{
		//sc::EventDispatcher dispatcher;
		//dispatcher.subscribe(this, &ExampleLayer::onKeyPressedEvent);
		//dispatcher.dispatch(event);

		if (event.type() == sc::EventType::KeyPressed)
		{
			auto asd = sc::Input::getKeyName(((sc::KeyPressedEvent&)event).getKeyCode());
			LOG_WARNING("%s", asd.c_str())

		}
	}

private:
	std::shared_ptr<sc::Shader> shader;
	std::shared_ptr<sc::VertexArray> _vertexArray;

	std::shared_ptr<sc::Shader> shader2;
	std::shared_ptr<sc::VertexArray> _vertexArray2;

	sc::OrthoCamera _camera;
	scmath::Vec3 _cameraPos;
	float _cameraMoveSpeed = 0.1f;
	float _cameraRot = 0.0f;
	float _cameraRotSpeed = 90.0f;
};

class Sandbox : public sc::Application
{
public:
	Sandbox() 
	{

		pushLayer(new ExampleLayer());
	}


	~Sandbox() {}
};

sc::Application* sc::CreateApplication()
{
	return new Sandbox();
}