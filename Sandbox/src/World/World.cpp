#include "World.h"


World::World() 
{
   _scenesMap["MainScene"] = std::make_shared<Scene>();
   setCurrentScene("MainScene");
}

ScenePtr World::getScene(std::string const& name) const
{
    SC_ASSERT(_scenesMap.find(name) != _scenesMap.end(), "No such scene: \"%s\"!", name.c_str());
    return _scenesMap.at(name);
}

ScenePtr World::getCurrentScene() const
{
    return _currentScene;
}

void World::addScene(std::string const& name, ScenePtr scene)
{
    SC_ASSERT(_scenesMap.find(_currentScene) != _scenesMap.end(), "Scene already exist: \"%s\"!", name.c_str());
    SC_ASSERT(scene, "Attempt to add empty scene: \"%s\"!", name.c_str());
    _scenesMap.insert_or_assign(name, scene);
}

void World::setCurrentScene(std::string const& name) 
{
    SC_ASSERT(_scenesMap.find(_currentScene) != _scenesMap.end(), "No such scene: \"%s\"!", name.c_str());
    _currentSceneName = name;
    _currentScene = _scenesMap[_currentSceneName];
}

void World::prepare() 
{
    _currentScene->prepare();
}

void World::animate(float deltaTime) 
{
    _currentScene->animate(deltaTime);
}

void World::processCollisions() 
{
    _currentScene->processCollisions();
}

void World::draw(sc::FPSCamera const& camera, sc::Lights const& lights) 
{
    _currentScene->draw(camera, lights);
}