#include "SimpleCanvas.h"

#include <memory>

class ExampleLayer : public sc::Layer
{
public:
	ExampleLayer()
	: Layer("Example")
	, _camera(-1.6f, 1.6f, -0.9f, 0.9f)
	, _cameraPos(0, 0, 1.0f)
	, _squarePos(0, 0, 0)
	{
		_triangleVAO.reset(sc::VertexArray::create());

		float triangleVAO[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		auto triangleVBO = sc::VertexBuffer::create(triangleVAO, sizeof(triangleVAO));

		sc::BufferLayout layout = {
			{ sc::ShaderDataType::Float3, "a_Position"},
			{ sc::ShaderDataType::Float4, "a_Color"}
		};

		triangleVBO->setLayout(layout);
		_triangleVAO->addVertexBuffer(triangleVBO);
		
		
		unsigned int indices[3] = { 0, 1, 2	};
		auto indexBuffer = sc::IndexBuffer::create(indices, 3);
		_triangleVAO->setIndexBuffer(indexBuffer);

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
		_triangleShader = std::make_unique<sc::Shader>(vertexSrc, fragmentSrc);


		_squareVAO.reset(sc::VertexArray::create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -1.0f, 0.0f, 1.0f
		};

		auto squareVBO = sc::VertexBuffer::create(squareVertices, sizeof(squareVertices));

		sc::BufferLayout layout2 = {
			{ sc::ShaderDataType::Float3, "a_Position"},
			{ sc::ShaderDataType::Float2, "a_TexCoord"}
		};

		squareVBO->setLayout(layout2);
		_squareVAO->addVertexBuffer(squareVBO);
		
		
		unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0 };
		auto indexBuffer2 = sc::IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
		_squareVAO->setIndexBuffer(indexBuffer2);

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


		_cubeVAO.reset(sc::VertexArray::create());

		float cubeVertices[7 * 8] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		auto cubeVBO = sc::VertexBuffer::create(cubeVertices, sizeof(cubeVertices));
		cubeVBO->setLayout(layout);
		_cubeVAO->addVertexBuffer(cubeVBO);


		unsigned int cubeIndices[] = {	
			0, 1, 2, 2, 3, 0, // front
			6, 5, 4, 4, 7, 6, // back
			3, 2, 6, 6, 7, 3, // top
			0, 4, 5, 5, 1, 0, // bottom
			4, 0, 3, 3, 7, 4, // left
			1, 5, 6, 6, 2, 1 // right
		};

		auto cubeIndexBuffer = sc::IndexBuffer::create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t));
		_cubeVAO->setIndexBuffer(cubeIndexBuffer);

		_chessboardShader = std::make_unique<sc::Shader>("C:\\Users\\Marcin\\Desktop\\mgr\\SimpleCanvas\\Sandbox\\assets\\textures\\shaders\\Texture.glsl");
		_chessboardTexture = sc::Texture2d::create("C:\\Users\\Marcin\\Desktop\\mgr\\SimpleCanvas\\Sandbox\\assets\\textures\\Checkerboard.png");
		_transparentTexture = sc::Texture2d::create("C:\\Users\\Marcin\\Desktop\\mgr\\SimpleCanvas\\Sandbox\\assets\\textures\\d4500b058db6706e4b28e2ab24c4e365.png");
		_chessboardShader->bind();
		_chessboardShader->uploadUniformInt("v_TexCoord", 0);
	}

	void update(float deltaTime) override
	{
		if (sc::Input::isKeyPressed(sc::KEY_UP))
		{
			_cameraPos.z -= _cameraMoveSpeed * deltaTime;
		}
		if (sc::Input::isKeyPressed(sc::KEY_DOWN))
		{
			_cameraPos.z += _cameraMoveSpeed * deltaTime;
		}

		if (sc::Input::isKeyPressed(sc::KEY_W))
		{
			_cameraPos.y += _cameraMoveSpeed * deltaTime;
		}
		if (sc::Input::isKeyPressed(sc::KEY_A))
		{
			_cameraPos.x -= _cameraMoveSpeed * deltaTime;
		}
		if (sc::Input::isKeyPressed(sc::KEY_S))
		{
			_cameraPos.y -= _cameraMoveSpeed * deltaTime;
		}
		if (sc::Input::isKeyPressed(sc::KEY_D))
		{
			_cameraPos.x += _cameraMoveSpeed * deltaTime;
		}

		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();

		_camera.setPosition(_cameraPos);
		
		sc::Renderer::beginScene(_camera);//----------------- BEGIN SCENE -------------------------
		
		scmath::Mat4 scale = scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f));

		_flatColorShader->bind();
		_flatColorShader->uploadUniformFloat4("u_Color", _squareColor);

		for (int y = 0; y < 20; y++)

		{
			for (int x = 0; x < 20; x++)
			{
				scmath::Vec3 pos(x * 0.11f, y * 0.11f, -0.4f);
				scmath::Mat4 transform = scmath::Mat4::translate(pos) * scale;
				sc::Renderer::submit(_squareVAO, _flatColorShader, transform);
			}
		}

		// square with chessboard
		_chessboardTexture->bind();
		sc::Renderer::submit(_squareVAO, _chessboardShader, scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f)));
		_transparentTexture->bind();
		sc::Renderer::submit(_squareVAO, _chessboardShader, scmath::Mat4::translate(scmath::Vec3(0.0f, 0.0f, 0.01f)) * scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f)));

		// triangle
		rotationTriangle += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
		scmath::Vec3 normalizedAxis(0.0f, 0.0f, 1.0f);
		scmath::Vec3 tranlPos(1.0f, 0.0f, 0.0f);
		sc::Renderer::submit(_triangleVAO, _triangleShader, scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::translate(tranlPos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f)));

		// cube
		scmath::Vec3 moveCube(0.5f, 0.0f, 0.0f);
		sc::Renderer::submit(_cubeVAO, _triangleShader, scmath::Mat4::translate(moveCube)* scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f)));

		sc::Renderer::endScene();		//---------------------------- END SCENE ---------------------------
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
	sc::ShaderPtr _triangleShader;
	sc::VertexArrayPtr _triangleVAO;

	float rotationTriangle = 0.0f;
	float rotationTriangleSpeed = 30.0f;

	sc::ShaderPtr _flatColorShader;
	sc::ShaderPtr _chessboardShader;
	sc::VertexArrayPtr _squareVAO;

	//cube
	sc::VertexArrayPtr _cubeVAO;

	sc::Texture2dPtr _chessboardTexture;
	sc::Texture2dPtr _transparentTexture;

	sc::OrthoCamera _camera;
	scmath::Vec3 _cameraPos;
	float _cameraMoveSpeed = 1.f;
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