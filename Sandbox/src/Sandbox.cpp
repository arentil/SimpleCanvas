#include "SimpleCanvas.h"
#include "SimpleCanvas/EntryPoint.h"

#include "TextureCube.h"
#include "ColorCube.h"
#include "Teapot.h"
#include "Sponza.h"
#include "Triangle.h"
#include "TileMap.h"
#include "BlendTexSquare.h"

#include <memory>
#include <filesystem>
#include <vector>

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
			7, 6, 2, 2, 3, 7, // top
			0, 1, 5, 5, 4, 0, // bottom
			4, 5, 6, 6, 7, 4, // fromt
			1, 0, 3, 3, 2, 1  // back
		};
		auto cubemapIndexBuffer = sc::IndexBuffer::create(cubemapIndices,  sizeof(cubemapIndices) / sizeof(uint32_t));
		_cubemapVAO->setIndexBuffer(cubemapIndexBuffer);

		_shadersContainer.addShaderFromFile("Cubemap", "assets/textures/shaders/Cubemap_vertex.glsl", "assets/textures/shaders/Cubemap_fragment.glsl");

		// END OF CUBEMAP

		_chessboardTexture = sc::Texture2d::create("assets/textures/Checkerboard.png");
		_transparentTexture = sc::Texture2d::create("assets/textures/d4500b058db6706e4b28e2ab24c4e365.png");

		_shadersContainer.addShaderFromFile("TexShader", "assets/textures/shaders/Tex_vertex.glsl", "assets/textures/shaders/Tex_fragment.glsl");
		_shadersContainer.addShaderFromFile("Flat", "assets/textures/shaders/Flat_vertex.glsl", "assets/textures/shaders/Flat_fragment.glsl");
		_shadersContainer.addShaderFromFile("FlatColor", "assets/textures/shaders/FlatColor_vertex.glsl", "assets/textures/shaders/FlatColor_fragment.glsl");
		_shadersContainer.addShaderFromFile("Triangle", "assets/textures/shaders/ViewProj_vertex.glsl", "assets/textures/shaders/ViewProj_fragment.glsl");
		_shadersContainer.addShaderFromFile("Texture", "assets/textures/shaders/Texture_vertex.glsl", "assets/textures/shaders/Texture_fragment.glsl");

		triangle = std::make_unique<Triangle>(*(_shadersContainer.getShader("Flat")), *(_cameraController.getCamera()));
		texCube = std::make_unique<TextureCube>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()), _chessboardTexture);
		colorCube = std::make_unique<ColorCube>(*(_shadersContainer.getShader("Flat")), *(_cameraController.getCamera()));
		teapot = std::make_unique<Teapot>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()));
		sponza = std::make_unique<Sponza>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()));
		tileMap = std::make_unique<TileMap>(*(_shadersContainer.getShader("Flat")), *(_cameraController.getCamera()));
		blendSquare = std::make_unique<BlendTexSquare>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()), _transparentTexture);
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
		sc::Renderer::submit(_cubemapVAO, cubemapShader, scmath::Mat4::translate(_cameraController.getCamera()->getPosition()));
		glDepthMask(GL_TRUE);

		// draw tilemaps
		tileMap->draw();

		// triangle
		rotationTriangle += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
		scmath::Vec3 normalizedAxis(0.0f, 0.0f, 1.0f);
		scmath::Vec3 tranlPos(1.0f, 0.0f, 0.0f);
		auto triangleMatrix = scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::translate(tranlPos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f));
		triangle->draw(triangleMatrix);

		// color cube
		scmath::Vec3 moveCube(0.5f, 0.0f, 0.0f);
		auto transform = scmath::Mat4::translate(moveCube) * scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f));
		colorCube->draw(transform);

		// textured cube
		scmath::Vec3 moveCube2(3.0f, 0.0f, 2.0f);
		texCube->draw(scmath::Mat4::translate(moveCube2) * scmath::Mat4::rotateY(scmath::degToRad(45.0f)));

		// teapot
		scmath::Vec3 teapotAxis(0.0f, 1.0f, 0.0f);
		teapot->draw(scmath::Mat4::translate(-2.0f, 0.0f, 2.0f) * scmath::Mat4::rotateY(rotationTriangle) * scmath::Mat4::scale(0.01f, 0.01f, 0.01f));

		// sponza (building)
		sponza->draw(scmath::Mat4::translate(0.0f, -1.0f, 0.0f));
		
		// square with blend texture - to draw blend texture, make sure to draw in in the last place
		auto transformBlend = scmath::Mat4::translate(scmath::Vec3(0.0f, 0.0f, 0.01f)) * scmath::Mat4::scale(scmath::Vec3(1.1f, 1.1f, 1.1f));
		blendSquare->draw(transformBlend);

		sc::Renderer::endScene();		//---------------------------- END SCENE ---------------------------
	}

	void onEvent(sc::Event &event) override
	{
		_cameraController.onEvent(event);
	}

private:
	sc::ShadersContainer _shadersContainer;

	float rotationTriangle = 0.0f;
	float rotationTriangleSpeed = 30.0f;

	sc::VertexArrayPtr _squareVAO;
	sc::Texture2dPtr _chessboardTexture;
	sc::Texture2dPtr _transparentTexture;

	sc::CameraController _cameraController;

	scmath::Vec4 _squareColor = {0.2f, 0.3f, 0.8f, 1.0f};

	sc::VertexArrayPtr _cubemapVAO;
	sc::CubemapPtr _cubemap;

	std::unique_ptr<Triangle> triangle;
	std::unique_ptr<TextureCube> texCube;
	std::unique_ptr<ColorCube> colorCube;
	std::unique_ptr<Teapot> teapot;
	std::unique_ptr<Sponza> sponza;
	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<BlendTexSquare> blendSquare;
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