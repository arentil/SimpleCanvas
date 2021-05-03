#include "Scene.h"

#include <Objects/Skybox.h>
#include <Objects/ColorCube.h>
#include <Objects/Triangle.h>
#include <Objects/Sponza.h>
#include <Objects/Terrain.h>
#include <Objects/TextureCube.h>
#include <Objects/Teapot.h>
#include <Objects/TileMap.h>
#include <Objects/BlendTexSquare.h>

Scene::Scene() 
{
    _shadersContainer.addShaderFromFile("Cubemap", "assets/shaders/Cubemap_vertex.glsl", "assets/shaders/Cubemap_fragment.glsl");
    skybox = std::make_shared<Skybox>(*getShader("Cubemap"));


    _shadersContainer.addShaderFromFile("Texture", "assets/shaders/Texture_vertex.glsl", "assets/shaders/Texture_fragment.glsl");
    _shadersContainer.addShaderFromFile("FlatColor", "assets/shaders/FlatColor_vertex.glsl", "assets/shaders/FlatColor_fragment.glsl");
    _chessboardTexture = sc::Texture2d::create("assets/textures/Checkerboard.png");
    _transparentTexture = sc::Texture2d::create("assets/textures/d4500b058db6706e4b28e2ab24c4e365.png");

    rootObject = std::make_shared<Terrain>(*getShader("FlatColor"));
        rootObject->attach(new Sponza(*getShader("Texture")));
        rootObject->attach(new ColorCube(*getShader("FlatColor")));
            rootObject->findChildByName("ColorCube")->attach(new Triangle(*getShader("FlatColor")));
        rootObject->attach(new TextureCube(*getShader("Texture"), _chessboardTexture));
        rootObject->attach(new Teapot(*getShader("Texture")));
        rootObject->attach(new TileMap(*getShader("FlatColor")));
        rootObject->attach(new BlendTexSquare(*getShader("Texture"), _transparentTexture));
}

void Scene::prepare() 
{
    rootObject->prepare();
}

void Scene::animate(float deltaTime) 
{
    rootObject->animate(deltaTime);
}

void Scene::processCollisions() 
{
    rootObject->processCollisions(rootObject.get());
}

void Scene::draw(sc::Camera const& camera, sc::Lights const& lights) 
{
    //skybox->draw(camera, lights);
    rootObject->draw(camera, lights);
}

sc::ShaderPtr Scene::getShader(std::string const& name)
{
    return _shadersContainer.getShader(name);
}