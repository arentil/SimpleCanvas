#pragma once

#include "SimpleCanvas.h"
#include "Scenes/Scene.h"

class World
{
public:
    World(sc::CameraController & camCtrl);
    virtual ~World() = default;

    ScenePtr getScene(std::string const& name) const;
    ScenePtr getCurrentScene() const;
    void addScene(std::string const& name, ScenePtr scene);
    void setCurrentScene(std::string const& name);

    virtual void loadWorld();
    virtual void unloadWorld() {}

    void prepare(float deltaTime);
    void physic();
    void collisionsCheck();
    void update();
    void lateUpdate();
    void draw(sc::CameraController const& camCtrl, sc::Lights const& lights);
    void destroyCheck();

private:
    sc::AssetsContainer _assets;
    
    std::map<std::string, ScenePtr> _scenesMap;
    std::string _currentSceneName;
    ScenePtr _currentScene;

    sc::ModelPtr createCubeModel() const;
};