#include "Scene.h"

#include <Objects/Skybox.h>
#include <Objects/ColorCube.h>
#include <Objects/Triangle.h>
#include <Objects/Gun.h>
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

    auto terrain = rootObject;
    
    Player *player = new Player(assets, camCtrl);
    player->attach(new Gun(assets));

    camCtrl.attachObject(player);
    terrain->attach(player);

    terrain->attach(new ColorCube(assets));
    auto colorCube = rootObject->findChildByName("ColorCube");
    colorCube->attach(new Triangle(assets));
    
    terrain->attach(new TextureCube(assets));
    terrain->attach(new Teapot(assets));
    terrain->attach(new TileMap(assets));
    terrain->attach(new BlendTexSquare(assets));
    
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

void Scene::destroy() 
{
    rootObject->destroy();
}