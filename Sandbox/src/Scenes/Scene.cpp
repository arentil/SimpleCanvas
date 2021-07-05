#include "Scene.h"

#include <Objects/Skybox.h>
#include <Objects/Gun.h>
#include <Objects/Building.h>
#include <Objects/Player.h>
#include <Objects/Terrain.h>
#include <Objects/Target.h>
#include <Objects/Crosshair.h>

Scene::Scene(sc::AssetsContainer &assets, sc::CameraController & camCtrl) 
{
    skybox = std::make_shared<Skybox>(assets, camCtrl);

    grassTerrain = std::make_shared<Terrain>(assets);
    createBuildings(grassTerrain, assets);
    
    // player
    Player *player = new Player(assets, camCtrl);
    grassTerrain->attach(player);
    camCtrl.attachObject(player);

    // gun
    player->attach(new Gun(assets));

    // crossfire
    player->attach(new Crosshair(assets));

    // generate targets and set their parents to terrain
    createTargets(grassTerrain, assets);
}

void Scene::prepare(float deltaTime) 
{
    grassTerrain->prepare(deltaTime);
}

void Scene::physic() 
{
    grassTerrain->physic();
}

void Scene::collisionsCheck() 
{
    grassTerrain->collisionsCheck();
}

void Scene::update()
{
    skybox->update();
    grassTerrain->update();
}

void Scene::lateUpdate() 
{
    grassTerrain->lateUpdate();
}

void Scene::draw(sc::CameraController const& camCtrl, sc::Lights const& lights) 
{
    skybox->draw(camCtrl, sc::Lights{}, scmath::Mat4::identity());
    grassTerrain->draw(camCtrl, lights, scmath::Mat4::identity());
}

void Scene::destroyCheck() 
{
    grassTerrain->destroyCheck();
}

void Scene::createTargets(std::shared_ptr<sc::SCObject> object, sc::AssetsContainer &assets) 
{
    int numberOfTargets = 20;
    float distBetweenTargets = 3.0f;

    scmath::Vec3 basePos(-5.0f, 5.0f, -20.0f);
    int targetsSqrt = std::sqrt(numberOfTargets);

    for (int i = 0; i < targetsSqrt; i++)
    {
        for (int j = 0; j < targetsSqrt; j++)
        {
            auto newTarget = new Target(assets);
            newTarget->Transform.Translation = basePos + scmath::Vec3(distBetweenTargets * i, distBetweenTargets * j, 0.0f);
            object->attach(newTarget);
        }
    }
}

void Scene::createBuildings(std::shared_ptr<sc::SCObject> object, sc::AssetsContainer &assets) 
{
    // way
    auto way = new Building(assets);
    way->Transform.Scale.x = 5.0f;
    way->Transform.Scale.z = 50.0f;
    way->Transform.Translation.z -= 6.0f;
    way->Transform.Translation.y = -2.0f;
    object->attach(way);

    // walls around terrain
    auto wall1 = new Building(assets);
    wall1->Transform.Scale.z = 12.0f;
    wall1->Transform.Scale.x = 1.0f;
    wall1->Transform.Scale.y = 5.0f;
    wall1->Transform.Translation.x -= 5.5f;
    wall1->Transform.Translation.z += 6.0f;
    wall1->Transform.Translation.y = -1.0f;
    object->attach(wall1);

        // walls around terrain
    auto wall2 = new Building(assets);
    wall2->Transform.Scale.z = 1.0f;
    wall2->Transform.Scale.x = 10.f;
    wall2->Transform.Scale.y = 5.0f;
    wall2->Transform.Translation.x = 0.0f;
    wall2->Transform.Translation.z += 6.0f;
    wall2->Transform.Translation.y = -1.0f;
    object->attach(wall2);

    // walls around terrain
    auto wall3 = new Building(assets);
    wall3->Transform.Scale.z = 12.0f;
    wall3->Transform.Scale.x = 1.0f;
    wall3->Transform.Scale.y = 5.0f;
    wall3->Transform.Translation.x += 5.5f;
    wall3->Transform.Translation.z += 6.0f;
    wall3->Transform.Translation.y = -1.0f;
    object->attach(wall3);

    // walls around terrain
    auto wall4 = new Building(assets);
    wall4->Transform.Scale.z = 1.0f;
    wall4->Transform.Scale.x = 3.0f;
    wall4->Transform.Scale.y = 3.0f;
    wall4->Transform.Translation.x += 4.0f;
    wall4->Transform.Translation.z -= 6.0f;
    wall4->Transform.Translation.y = -1.0f;
    object->attach(wall4);

    // walls around terrain
    auto wall5 = new Building(assets);
    wall5->Transform.Scale.z = 1.0f;
    wall5->Transform.Scale.x = 3.0f;
    wall5->Transform.Scale.y = 3.0f;
    wall5->Transform.Translation.x -= 4.0f;
    wall5->Transform.Translation.z -= 6.0f;
    wall5->Transform.Translation.y = -1.0f;
    object->attach(wall5);

        // walls around terrain
    auto wall6 = new Building(assets);
    wall6->Transform.Scale.z = 1.0f;
    wall6->Transform.Scale.x = 12.0f;
    wall6->Transform.Scale.y = 2.0f;
    wall6->Transform.Translation.x = 0.0f;
    wall6->Transform.Translation.z -= 6.0f;
    wall6->Transform.Translation.y = 1.5f;
    object->attach(wall6);
}
