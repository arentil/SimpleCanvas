#include "SimpleCanvas.h"
#include "SimpleCanvas/EntryPoint.h"

#include "Objects/Skybox.h"

#include "World/World.h"

#include <memory>
#include <filesystem>
#include <vector>

class SimpleGameCanvas : public sc::Canvas
{
public:
	SimpleGameCanvas()
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

		scmath::Vec3 diffusePos(0.0f, 10.0f, -20.0f);
		float specularStrength = 1.0f;
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

class SimpleGame : public sc::Application
{
public:
	SimpleGame()
	{
		initCanvas(new SimpleGameCanvas());
		LOG_INFO("LOG_INFO - white!")
		LOG_OK("LOG_OK - green!")
		LOG_WARNING("LOG_WARNING - yellow!")
		LOG_ERROR("LOG_ERROR - red!")
	}

	~SimpleGame() {}
};

sc::Application* sc::CreateApplication()
{
	return new SimpleGame();
}