#include "SimpleCanvas.h"
#include "SimpleCanvas/EntryPoint.h"

#include "Objects/Skybox.h"

#include "World/World.h"

#include <memory>
#include <filesystem>
#include <vector>

class ExampleCanvas : public sc::Canvas
{
public:
	ExampleCanvas()
	: cameraSettings
		{ 
			70,			// fov
		  	1280,		// aspect ratio width
		  	720,		// aspect ratio height
		  	0.01f,		// camera near plane distance
			100			// camera far plane distance
		}								
	, camCtrl(cameraSettings)
	{
		world = std::make_unique<World>(camCtrl);
	}

	void update(float deltaTime) override
	{
		sc::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
		sc::RenderCommand::clear();

		scmath::Vec3 diffusePos(0.0f, 4.0f, 0.0f);
		float specularStrength = 0.5f;
		sc::Lights lights{0.3f, diffusePos, specularStrength};

		world->prepare(deltaTime);
		camCtrl.update(deltaTime);
		world->physic();
		world->collisionsCheck();
		world->update();
		world->lateUpdate();
		world->draw(camCtrl, lights);
		world->destroyCheck();
	}

	void onEvent(sc::Event &event) override
	{
		camCtrl.onEvent(event);
	}

private:
	sc::CameraSettings cameraSettings;
	sc::CameraController camCtrl;
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