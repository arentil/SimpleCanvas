#include "Scene.h"

#include <Objects/Skybox.h>
#include <Objects/ColorCube.h>
#include <Objects/Triangle.h>
#include <Objects/Player.h>
#include <Objects/Terrain.h>
#include <Objects/TextureCube.h>
#include <Objects/Teapot.h>
#include <Objects/TileMap.h>
#include <Objects/BlendTexSquare.h>

Scene::Scene(sc::AssetsContainer &assets, sc::FPSCamera & camera) 
{
    skybox = std::make_shared<Skybox>(assets, camera);

    rootObject = std::make_shared<Terrain>(assets);
    {
        rootObject->attach(new Player(assets, camera));
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

void Scene::prepare(float deltaTime) 
{
    rootObject->prepare(deltaTime);
}

void Scene::physic() 
{
    rootObject->physic();
}

void Scene::update()
{
    skybox->update();
    rootObject->update();
}

void Scene::checkCollision() 
{
    rootObject->checkCollision(rootObject.get());
}

void Scene::draw(sc::FPSCamera const& camera, sc::Lights const& lights) 
{
    skybox->draw(camera, sc::Lights{}, scmath::Mat4::identity());
    rootObject->draw(camera, lights, scmath::Mat4::identity());
}