#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox;
class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Scene
{
public:
    Scene(sc::AssetsContainer &assets);
    virtual ~Scene() = default;

    virtual void loadScene() {};

    void prepare();
    void animate(float deltaTime);
    void processCollisions();
    void draw(sc::FPSCamera const& camera, sc::Lights const& lights);

private:
    std::shared_ptr<sc::SCObject> rootObject;
    std::shared_ptr<Skybox> skybox;
};