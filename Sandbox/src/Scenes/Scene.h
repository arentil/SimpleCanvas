#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox;
class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Scene
{
public:
    Scene(sc::AssetsContainer &assets, sc::CameraController & camCtrl);
    virtual ~Scene() = default;

    virtual void loadScene() {};

    void prepare(float deltaTime);
    void physic();
    void checkCollision();
    void update();
    void draw(sc::CameraController const& camCtrl, sc::Lights const& lights);

private:
    std::shared_ptr<sc::SCObject> rootObject;
    std::shared_ptr<Skybox> skybox;
};