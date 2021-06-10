#include "World.h"

World::World(sc::CameraController & camCtrl)
{
    loadWorld();
   _scenesMap["MainScene"] = std::make_shared<Scene>(_assets, camCtrl);
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
    SC_ASSERT(_scenesMap.find(name) != _scenesMap.end(), "Scene already exist: \"%s\"!", name.c_str());
    SC_ASSERT(scene, "Attempt to add empty scene: \"%s\"!", name.c_str());
    _scenesMap.insert_or_assign(name, scene);
}

void World::setCurrentScene(std::string const& name) 
{
    SC_ASSERT(_scenesMap.find(name) != _scenesMap.end(), "No such scene: \"%s\"!", name.c_str());
    _currentSceneName = name;
    _currentScene = _scenesMap[_currentSceneName];
}

void World::prepare(float deltaTime) 
{
    _currentScene->prepare(deltaTime);
}

void World::physic()
{
    _currentScene->physic();
}

void World::lateUpdate() 
{
    _currentScene->lateUpdate();
}

void World::update()
{
    _currentScene->update();
}

void World::draw(sc::CameraController const& camCtrl, sc::Lights const& lights) 
{
    _currentScene->draw(camCtrl, lights);
}

void World::destroy() 
{
    _currentScene->destroy();
}

void World::loadWorld() 
{
    //_assets.Models.addModelFromFile("Sponza", "assets/models/sponza/sponza.obj");
    _assets.Models.addModelFromFile("Teapot", "assets/models/teapot/teapot.obj");

    _assets.Shaders.addShaderFromFile("Skybox", "assets/shaders/Cubemap_vertex.glsl", "assets/shaders/Cubemap_fragment.glsl");
    _assets.Shaders.addShaderFromFile("Texture", "assets/shaders/Texture_vertex.glsl", "assets/shaders/Texture_fragment.glsl");
    _assets.Shaders.addShaderFromFile("FlatColor", "assets/shaders/FlatColor_vertex.glsl", "assets/shaders/FlatColor_fragment.glsl");

    _assets.Textures.addTexture2dFromFile("Chess", "assets/textures/Checkerboard.png");
    _assets.Textures.addTexture2dFromFile("Blend", "assets/textures/d4500b058db6706e4b28e2ab24c4e365.png");

    std::vector<std::string> cubemapFacesFiles
    {
        "assets/textures/skybox/right.jpg",
        "assets/textures/skybox/left.jpg",
        "assets/textures/skybox/top.jpg",
        "assets/textures/skybox/bottom.jpg",
        "assets/textures/skybox/front.jpg",
        "assets/textures/skybox/back.jpg"
    };
    _assets.Textures.addCubemapFromFile("Skybox", cubemapFacesFiles);

}