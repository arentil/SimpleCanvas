#include "SimpleCanvas.h"

#include <memory>
#include <filesystem>

class ExampleLayer : public sc::Layer
{
public:
	ExampleLayer()
	: Layer("Example")
	, _cameraController(16.0f, 9.0f)//1280.0f / 720.0f)
	{
		std::vector<std::string> cubemapFacesFiles
		{
			"assets/textures/skybox/right.jpg",
			"assets/textures/skybox/left.jpg",
			"assets/textures/skybox/top.jpg",
			"assets/textures/skybox/bottom.jpg",
			"assets/textures/skybox/front.jpg",
			"assets/textures/skybox/back.jpg"
		};
		_cubemap.reset(new sc::Cubemap(cubemapFacesFiles));
		_cubemapVAO.reset(sc::VertexArray::create());
		float cubemapVAO[8 * 3] = {
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f
		};
		auto cubemapVBO = sc::VertexBuffer::create(cubemapVAO, sizeof(cubemapVAO));
		sc::BufferLayout cubemapLayout = {
			{ sc::ShaderDataType::Float3, "aPos"}
		};

		cubemapVBO->setLayout(cubemapLayout);
		_cubemapVAO->addVertexBuffer(cubemapVBO);

		unsigned int cubemapIndices[] = { 
			5, 1, 2, 2, 6 ,5, // right
			0, 4, 7, 7, 3, 0, // left
			7, 6, 2, 2, 7, 3, // top
			0, 1, 5, 5, 4, 0, // bottom
			4, 5, 6, 6, 7, 4, // fromt
			1, 0, 3, 3, 2, 1  // back
		};
		auto cubemapIndexBuffer = sc::IndexBuffer::create(cubemapIndices,  sizeof(cubemapIndices) / sizeof(uint32_t));
		_cubemapVAO->setIndexBuffer(cubemapIndexBuffer);

		_shadersContainer.addShaderFromFile("Cubemap", "assets/textures/shaders/Cubemap_vertex.glsl", "assets/textures/shaders/Cubemap_fragment.glsl");

		// END OF CUBEMAP

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

		_shadersContainer.addShaderFromFile("Triangle", "assets/textures/shaders/ViewProj_vertex.glsl", "assets/textures/shaders/ViewProj_fragment.glsl");


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

		_shadersContainer.addShaderFromFile("FlatColor", "assets/textures/shaders/FlatColor_vertex.glsl", "assets/textures/shaders/FlatColor_fragment.glsl");

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
	

		// draw skybox first
		glDepthMask(GL_FALSE);
		auto cubemapShader = _shadersContainer.getShader("Cubemap");
		cubemapShader->bind();
		_cubemap->bind();
		//scmath::Mat4 scaleCubemap = scmath::Mat4::scale(scmath::Vec3(4.0f, 4.0f, 4.0f));
		sc::Renderer::submit(_cubemapVAO, cubemapShader, scmath::Mat4::translate(_cameraController.getCamera()->getPosition()));
		glDepthMask(GL_TRUE);


		scmath::Mat4 scale = scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f));
		auto flatColorShader = _shadersContainer.getShader("FlatColor");
		flatColorShader->bind();
		flatColorShader->uploadUniformFloat4("u_Color", _squareColor);
		for (int y = 0; y < 20; y++)

		{
			for (int x = 0; x < 20; x++)
			{
				scmath::Vec3 pos(x * 0.11f, y * 0.11f, -0.4f);
				scmath::Mat4 transform = scmath::Mat4::translate(pos) * scale;
				sc::Renderer::submit(_squareVAO, flatColorShader, transform);
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
		sc::Renderer::submit(_triangleVAO,  _shadersContainer.getShader("Triangle"), scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::translate(tranlPos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f)));

		// cube
		scmath::Vec3 moveCube(0.5f, 0.0f, 0.0f);
		sc::Renderer::submit(_cubeVAO, _shadersContainer.getShader("Triangle"), scmath::Mat4::translate(moveCube)* scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f)));

		sc::Renderer::endScene();		//---------------------------- END SCENE ---------------------------
	}

	void onEvent(sc::Event &event) override
	{
		_cameraController.onEvent(event);
	}

private:
	sc::ShadersContainer _shadersContainer;

	sc::VertexArrayPtr _triangleVAO;

	float rotationTriangle = 0.0f;
	float rotationTriangleSpeed = 30.0f;

	sc::VertexArrayPtr _squareVAO;

	//cube
	sc::VertexArrayPtr _cubeVAO;

	sc::Texture2dPtr _chessboardTexture;
	sc::Texture2dPtr _transparentTexture;

	sc::CameraController _cameraController;

	float _squareMoveSpeed = 1.0f;

	scmath::Vec4 _squareColor = {0.2f, 0.3f, 0.8f, 1.0f};

	sc::VertexArrayPtr _cubemapVAO;
	sc::CubemapPtr _cubemap;
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