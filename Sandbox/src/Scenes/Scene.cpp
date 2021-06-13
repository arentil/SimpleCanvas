#include "Scene.h"

#include <Objects/Skybox.h>
#include <Objects/Triangle.h>
#include <Objects/Gun.h>
#include <Objects/Player.h>
#include <Objects/Terrain.h>

Scene::Scene(sc::AssetsContainer &assets, sc::CameraController & camCtrl) 
{
    skybox = std::make_shared<Skybox>(assets, camCtrl);
    rootObject = std::make_shared<Terrain>(assets);

    // terrain (root)
    auto terrain = rootObject;
    
    // player
    Player *player = new Player(assets, camCtrl);
    terrain->attach(player);
    camCtrl.attachObject(player);

    // gun
    player->attach(new Gun(assets));
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

void Scene::lateUpdate() 
{
    rootObject->lateUpdate();
}

void Scene::draw(sc::CameraController const& camCtrl, sc::Lights const& lights) 
{
    skybox->draw(camCtrl, sc::Lights{}, scmath::Mat4::identity());
    rootObject->draw(camCtrl, lights, scmath::Mat4::identity());
}

void Scene::destroyCheck() 
{
    rootObject->destroyCheck();
}