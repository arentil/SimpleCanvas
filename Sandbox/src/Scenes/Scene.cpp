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

Scene::Scene(sc::AssetsContainer &assets, sc::CameraController & camCtrl) 
{
    skybox = std::make_shared<Skybox>(assets, camCtrl);

    rootObject = std::make_shared<Terrain>(assets);
    {
        Player *player = new Player(assets, camCtrl);
        camCtrl.attachObject(player);
        rootObject->attach(player);
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
    //rootObject->checkCollision(rootObject.get());
}

void Scene::draw(sc::CameraController const& camCtrl, sc::Lights const& lights) 
{
    skybox->draw(camCtrl, sc::Lights{}, scmath::Mat4::identity());
    rootObject->draw(camCtrl, lights, scmath::Mat4::identity());
}