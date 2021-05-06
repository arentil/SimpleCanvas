#include "SimpleCanvas.h"
#include "SimpleCanvas/EntryPoint.h"

#include "Objects/Skybox.h"
#include "Objects/ColorCube.h"
#include "Objects/BlendTexSquare.h"

#include "World/World.h"

#include <memory>
#include <filesystem>
#include <vector>

class ExampleCanvas : public sc::Canvas
{
public:
	ExampleCanvas()
	: _camera(scmath::Vec3(0.0f, 0.0f, 3.0f))
	{
		world = std::make_unique<World>(_camera);
	}

	void update(float deltaTime) override
	{
		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();

		_camera.update(deltaTime);

		scmath::Vec3 diffusePos(0.0f, 4.0f, 0.0f);
		float specularStrength = 0.5f;
		sc::Lights lights{0.3f, diffusePos, specularStrength};

		world->prepare();
		world->animate(deltaTime);
		world->processCollisions();
		world->draw(_camera, lights);
	}

	void onEvent(sc::Event &event) override
	{
		_camera.onEvent(event);
	}

private:
	sc::FPSCamera _camera;
	std::unique_ptr<World> world;
};

class Sandbox : public sc::Application
{
public:
	Sandbox()
	{
		initCanvas(new ExampleCanvas());
	}

	~Sandbox() {}
};

sc::Application* sc::CreateApplication()
{
	return new Sandbox();
}