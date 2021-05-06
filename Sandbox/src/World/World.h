#pragma once

#include "SimpleCanvas.h"
#include "Scenes/Scene.h"

class World
{
public:
    World(sc::FPSCamera const& camera);
    virtual ~World() = default;

    ScenePtr getScene(std::string const& name) const;
    ScenePtr getCurrentScene() const;
    void addScene(std::string const& name, ScenePtr scene);
    void setCurrentScene(std::string const& name);

    virtual void loadWorld();
    virtual void unloadWorld() {}

    void prepare();
    void animate(float deltaTime);
    void processCollisions();
    void draw(sc::FPSCamera const& camera, sc::Lights const& lights);

private:
    sc::AssetsContainer _assets;
    
    std::map<std::string, ScenePtr> _scenesMap;
    std::string _currentSceneName;
    ScenePtr _currentScene;
    sc::FPSCamera const& _camera;
};