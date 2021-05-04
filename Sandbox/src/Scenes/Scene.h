#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox;
class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    virtual void loadScene() {};

    void prepare();
    void animate(float deltaTime);
    void processCollisions();
    // void process input() ??????
    void draw(sc::FPSCamera const& camera, sc::Lights const& lights);

private:
    sc::ShaderPtr getShader(std::string const& name);

    sc::ShadersContainer _shadersContainer;
    sc::TexturePtr _chessboardTexture;
	sc::TexturePtr _transparentTexture;

    std::shared_ptr<sc::SCObject> rootObject;
    std::shared_ptr<Skybox> skybox;
};