#include "SimpleCanvas.h"

#include <memory>

class ExampleLayer : public sc::Layer
{
public:
	ExampleLayer()
	: Layer("Example")
	, _camera(-1.6f, 1.6f, -0.9f, 0.9f)
	, _cameraPos(0, 0, 0)
	, _squarePos(0, 0, 0)
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
			uniform mat4 u_Model;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
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
		shader = std::make_unique<sc::Shader>(vertexSrc, fragmentSrc);

		_vertexArray2.reset(sc::VertexArray::create());

		float vertices2[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		auto vertexBuffer2 =sc::VertexBuffer::create(vertices2, sizeof(vertices2));

		sc::BufferLayout layout2 = {
			{ sc::ShaderDataType::Float3, "a_Position"},
			{ sc::ShaderDataType::Float2, "a_TexCoord"}
		};

		vertexBuffer2->setLayout(layout2);
		_vertexArray2->addVertexBuffer(vertexBuffer2);
		
		
		unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0 };
		auto indexBuffer2 = sc::IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
		_vertexArray2->setIndexBuffer(indexBuffer2);

		std::string flatColorVertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 a_color;

			uniform vec4 u_Color;

			void main()
			{
				a_color = u_Color;
			}
		)";

		_flatColorShader = std::make_unique<sc::Shader>(flatColorVertexShaderSrc, flatColorFragmentShaderSrc);


		std::string texShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string texShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 a_color;

			in vec2 v_TexCoord;

			uniform vec4 u_Color;

			void main()
			{
				a_color = vec4(v_TexCoord, 0.0, 1.0);
			}
		)";

		_texShader = std::make_unique<sc::Shader>(texShaderVertexSrc, texShaderFragmentSrc);
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
		
		sc::Renderer::beginScene(_camera);//----------------- BEGIN SCENE -------------------------
		
		scmath::Mat4 scale = scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f));

		_flatColorShader->bind();
		_flatColorShader->uploadUniformFloat4("u_Color", _squareColor);

		for (int y = 0; y < 20; y++)

		{
			for (int x = 0; x < 20; x++)
			{
				scmath::Vec3 pos(x * 0.11f, y * 0.11f, 0);
				scmath::Mat4 transform = scmath::Mat4::translate(pos) * scale;
				sc::Renderer::submit(_vertexArray2, _flatColorShader, transform);
			}
		}

		sc::Renderer::submit(_vertexArray2, _texShader, scmath::Mat4::scale(scmath::Vec3(1.5f, 1.5f, 1.5f)));

		// triangle
		//sc::Renderer::submit(_vertexArray, shader);
		
		sc::Renderer::endScene();//---------------------------- END SCENE ---------------------------
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
	sc::ShaderPtr shader;
	sc::VertexArrayPtr _vertexArray;

	sc::ShaderPtr _flatColorShader;
	sc::ShaderPtr _texShader;
	sc::VertexArrayPtr _vertexArray2;

	sc::OrthoCamera _camera;
	scmath::Vec3 _cameraPos;
	float _cameraMoveSpeed = 5.f;
	float _cameraRot = 0.0f;
	float _cameraRotSpeed = 90.0f;
	scmath::Vec3 _squarePos;
	float _squareMoveSpeed = 1.0f;

	scmath::Vec4 _squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
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