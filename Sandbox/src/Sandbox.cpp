#include "SimpleCanvas.h"

#include <memory>
#include <filesystem>

class ExampleLayer : public sc::Layer
{
public:
	ExampleLayer()
	: Layer("Example")
	, _cameraController(16.0f, 9.0f)//1280.0f / 720.0f)
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

		_shadersContainer.addShaderFromFile("TriangleShader", "assets/textures/shaders/ViewProj_vertex.glsl", "assets/textures/shaders/ViewProj_fragment.glsl");
		_triangleShader = _shadersContainer.getShader("TriangleShader");


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

		_shadersContainer.addShaderFromFile("FlatColorShader", "assets/textures/shaders/FlatColor_vertex.glsl", "assets/textures/shaders/FlatColor_fragment.glsl");
		_flatColorShader = _shadersContainer.getShader("FlatColorShader");

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

		_chessboardTexture = sc::Texture2d::create("assets/textures/Checkerboard.png");
		_transparentTexture = sc::Texture2d::create("assets/textures/d4500b058db6706e4b28e2ab24c4e365.png");

		_shadersContainer.addShaderFromFile("Texture", "assets/textures/shaders/Texture_vertex.glsl", "assets/textures/shaders/Texture_fragment.glsl");
		auto textureShader = _shadersContainer.getShader("Texture");
		textureShader->bind();
		textureShader->uploadUniformInt("v_TexCoord", 0);
	}

	void update(float deltaTime) override
	{
		_cameraController.onUpdate(deltaTime);
		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();		
		sc::Renderer::beginScene(*(_cameraController.getCamera()));		//----------------- BEGIN SCENE -------------------------
		
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

		// square with chessboard texture
		_chessboardTexture->bind();
		sc::Renderer::submit(_squareVAO, _shadersContainer.getShader("Texture"), scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f)));

		// square with blend texture
		_transparentTexture->bind();
		sc::Renderer::submit(_squareVAO, _shadersContainer.getShader("Texture"), scmath::Mat4::translate(scmath::Vec3(0.0f, 0.0f, 0.01f)) * scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f)));

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
		_cameraController.onEvent(event);
		if (event.type() == sc::EventType::KeyPressed)
		{
			auto asd = sc::Input::getKeyName(((sc::KeyPressedEvent&)event).getKeyCode());
			LOG_WARNING("%s", asd.c_str());
		}
		else if (event.type() == sc::EventType::MouseScrolled)
		{
			auto asd = ((sc::MouseScrollEvent&)event).name();
			LOG_WARNING("%s", asd.c_str());
		}
	}

private:
	sc::ShadersContainer _shadersContainer;

	sc::ShaderPtr _triangleShader;
	sc::VertexArrayPtr _triangleVAO;

	float rotationTriangle = 0.0f;
	float rotationTriangleSpeed = 30.0f;

	sc::ShaderPtr _flatColorShader;
	sc::VertexArrayPtr _squareVAO;

	//cube
	sc::VertexArrayPtr _cubeVAO;

	sc::Texture2dPtr _chessboardTexture;
	sc::Texture2dPtr _transparentTexture;

	sc::CameraController _cameraController;

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