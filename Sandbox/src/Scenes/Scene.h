#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void loadScene() {};

    void prepare();
    void animate(float deltaTime);
    void processCollisions();
    // void input() ??????
    void draw(sc::Camera const& camera, sc::Lights const& lights);

private:
    std::shared_ptr<sc::SCObject> rootObject;
};