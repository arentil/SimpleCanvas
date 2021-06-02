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

Scene::Scene(sc::AssetsContainer &assets, sc::FPSCamera const& camera) 
{
    skybox = std::make_shared<Skybox>(assets, camera);

    rootObject = std::make_shared<Terrain>(assets);
    {
        //rootObject->attach(new Sponza(assets));
        rootObject->attach(new ColorCube(assets));
        {
            rootObject->findChildByName("ColorCube")->attach(new Triangle(assets));
        }
        rootObject->attach(new TextureCube(assets));
        rootObject->attach(new Teapot(assets));
        rootObject->attach(new TileMap(assets));
        rootObject->attach(new BlendTexSquare(assets));
    }
}

void Scene::prepare() 
{
    rootObject->prepare();
}

void Scene::animate(float deltaTime) 
{
    skybox->animate(deltaTime);
    rootObject->animate(deltaTime);
}

void Scene::processCollisions() 
{
    rootObject->processCollisions(rootObject.get());
}

void Scene::draw(sc::FPSCamera const& camera, sc::Lights const& lights) 
{
    skybox->draw(camera, sc::Lights{}, scmath::Mat4::identity());
    rootObject->draw(camera, lights, scmath::Mat4::identity());
}