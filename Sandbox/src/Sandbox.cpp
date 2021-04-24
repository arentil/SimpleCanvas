#include "SimpleCanvas.h"
#include "SimpleCanvas/EntryPoint.h"

#include "Skybox.h"
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

		cubemap = sc::Cubemap::create(cubemapFacesFiles);

		_chessboardTexture = sc::Texture2d::create("assets/textures/Checkerboard.png");
		_transparentTexture = sc::Texture2d::create("assets/textures/d4500b058db6706e4b28e2ab24c4e365.png");
		
		_shadersContainer.addShaderFromFile("Cubemap", "assets/textures/shaders/Cubemap_vertex.glsl", "assets/textures/shaders/Cubemap_fragment.glsl");
		_shadersContainer.addShaderFromFile("TexShader", "assets/textures/shaders/Texture_vertex.glsl", "assets/textures/shaders/Texture_fragment.glsl");
		_shadersContainer.addShaderFromFile("FlatColor", "assets/textures/shaders/FlatColor_vertex.glsl", "assets/textures/shaders/FlatColor_fragment.glsl");

		skybox = std::make_unique<Skybox>(*(_shadersContainer.getShader("Cubemap")), *(_cameraController.getCamera()), cubemap);
		triangle = std::make_unique<Triangle>(*(_shadersContainer.getShader("FlatColor")), *(_cameraController.getCamera()));
		texCube = std::make_unique<TextureCube>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()), _chessboardTexture);
		colorCube = std::make_unique<ColorCube>(*(_shadersContainer.getShader("FlatColor")), *(_cameraController.getCamera()));
		teapot = std::make_unique<Teapot>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()));
		sponza = std::make_unique<Sponza>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()));
		tileMap = std::make_unique<TileMap>(*(_shadersContainer.getShader("FlatColor")), *(_cameraController.getCamera()));
		blendSquare = std::make_unique<BlendTexSquare>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()), _transparentTexture);
	}

	void update(float deltaTime) override
	{
		_cameraController.onUpdate(deltaTime);
		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();		
		sc::Renderer::beginScene(*(_cameraController.getCamera()));		//----------------- BEGIN SCENE -------------------------

		skybox->draw(scmath::Mat4::translate(_cameraController.getCamera()->getPosition()));

		scmath::Vec3 diffusePos(0.0f, 4.0f, 0.0f);            //_cameraController.getCamera()->getPosition();


		sc::Material material{0.3f, diffusePos};
		colorCube->draw(material, scmath::Mat4::translate(diffusePos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f)));

		// draw tilemaps
		tileMap->draw(material);

		// triangle
		rotationTriangle += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
		scmath::Vec3 normalizedAxis(0.0f, 0.0f, 1.0f);
		scmath::Vec3 tranlPos(1.0f, 0.0f, 0.0f);
		auto triangleMatrix = scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::translate(tranlPos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f));
		triangle->draw(material, triangleMatrix);

		// color cube
		scmath::Vec3 moveCube(0.5f, 0.0f, 0.0f);
		auto transform = scmath::Mat4::translate(moveCube) * scmath::Mat4::rotate(rotationTriangle, normalizedAxis) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f));
		colorCube->draw(material, transform);

		// textured cube
		scmath::Vec3 moveCube2(3.0f, 0.0f, 2.0f);
		texCube->draw(material, scmath::Mat4::translate(moveCube2) * scmath::Mat4::rotateY(scmath::degToRad(45.0f)));

		// teapot
		scmath::Vec3 teapotAxis(0.0f, 1.0f, 0.0f);
		teapot->draw(material, scmath::Mat4::translate(-2.0f, 0.0f, 2.0f) * scmath::Mat4::rotateY(rotationTriangle) * scmath::Mat4::scale(0.01f, 0.01f, 0.01f));

		// sponza (building)
		sponza->draw(material, scmath::Mat4::translate(0.0f, -1.0f, 0.0f) * scmath::Mat4::scale(0.01f, 0.01f, 0.01f));
		
		// square with blend texture - to draw blend texture, make sure to draw in in the last place
		auto transformBlend = scmath::Mat4::translate(scmath::Vec3(0.0f, 0.0f, 0.01f)) * scmath::Mat4::scale(scmath::Vec3(1.1f, 1.1f, 1.1f));
		blendSquare->draw(material, transformBlend);

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
	sc::TexturePtr _chessboardTexture;
	sc::TexturePtr _transparentTexture;

	sc::CameraController _cameraController;

	scmath::Vec4 _squareColor = {0.2f, 0.3f, 0.8f, 1.0f};

	sc::TexturePtr cubemap;
	std::unique_ptr<Skybox> skybox;

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