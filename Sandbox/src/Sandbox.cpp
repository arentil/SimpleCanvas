#include "SimpleCanvas.h"
#include "SimpleCanvas/EntryPoint.h"

#include "Objects/Skybox.h"
#include "Objects/ColorCube.h"
#include "Objects/BlendTexSquare.h"

#include "World/World.h"

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

		_transparentTexture = sc::Texture2d::create("assets/textures/d4500b058db6706e4b28e2ab24c4e365.png");

		_shadersContainer.addShaderFromFile("Cubemap", "assets/shaders/Cubemap_vertex.glsl", "assets/shaders/Cubemap_fragment.glsl");
		_shadersContainer.addShaderFromFile("TexShader", "assets/shaders/Texture_vertex.glsl", "assets/shaders/Texture_fragment.glsl");

		skybox = std::make_unique<Skybox>(*(_shadersContainer.getShader("Cubemap")), *(_cameraController.getCamera()), cubemap);
		blendSquare = std::make_unique<BlendTexSquare>(*(_shadersContainer.getShader("TexShader")), *(_cameraController.getCamera()), _transparentTexture);

		world = std::make_unique<World>();
	}

	void update(float deltaTime) override
	{
		//int fps = 1.0f / deltaTime;

		_cameraController.onUpdate(deltaTime);
		auto camera = *(_cameraController.getCamera());
		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();
		sc::Renderer::beginScene(camera);
		

		skybox->draw(scmath::Mat4::translate(camera.getPosition()));

		scmath::Vec3 diffusePos(0.0f, 4.0f, 0.0f);
		float specularStrength = 0.5f;
		sc::Lights lights{0.3f, diffusePos, specularStrength};
		//colorCube->draw(lights, scmath::Mat4::translate(diffusePos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f)));


		world->prepare();
		world->animate(deltaTime);
		world->processCollisions();
		world->draw(camera, lights);

		// square with blend texture - to draw blend texture, make sure to draw in in the last place
		auto transformBlend = scmath::Mat4::translate(scmath::Vec3(0.0f, 0.0f, 0.01f)) * scmath::Mat4::scale(scmath::Vec3(1.1f, 1.1f, 1.1f));
		blendSquare->draw(lights, transformBlend);

		sc::Renderer::endScene();
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
	sc::TexturePtr _transparentTexture;

	sc::CameraController _cameraController;


	sc::TexturePtr cubemap;
	std::unique_ptr<Skybox> skybox;

	std::unique_ptr<ColorCube> colorCube;
	std::unique_ptr<BlendTexSquare> blendSquare;

	std::unique_ptr<World> world;
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