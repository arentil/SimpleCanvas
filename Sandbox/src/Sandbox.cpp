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
		world = std::make_unique<World>();
	}

	void update(float deltaTime) override
	{
		//int fps = 1.0f / deltaTime;

		_cameraController.onUpdate(deltaTime);
		sc::Camera const& camera = *(_cameraController.getCamera());
		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();
		sc::Renderer::beginScene(camera);

		scmath::Vec3 diffusePos(0.0f, 4.0f, 0.0f);
		float specularStrength = 0.5f;
		sc::Lights lights{0.3f, diffusePos, specularStrength};

		world->prepare();
		world->animate(deltaTime);
		world->processCollisions();
		world->draw(camera, lights);

		sc::Renderer::endScene();
	}

	void onEvent(sc::Event &event) override
	{
		_cameraController.onEvent(event);
	}

private:
	sc::CameraController _cameraController;
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