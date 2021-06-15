#include "Scene.h"

#include <Objects/Skybox.h>
#include <Objects/Triangle.h>
#include <Objects/Gun.h>
#include <Objects/Player.h>
#include <Objects/Terrain.h>
#include <Objects/Target.h>

Scene::Scene(sc::AssetsContainer &assets, sc::CameraController & camCtrl) 
{
    skybox = std::make_shared<Skybox>(assets, camCtrl);
    terrain = std::make_shared<Terrain>(assets);
    
    // player
    Player *player = new Player(assets, camCtrl);
    terrain->attach(player);
    camCtrl.attachObject(player);

    // gun
    player->attach(new Gun(assets));

    // generate targets and set their parents to terrain
    //createTargets(terrain, assets);

    // generate center target

    auto target = new Target(assets);
    terrain->attach(target);
    target->Transform.Translation.y -= 4.0f;

}

void Scene::prepare(float deltaTime) 
{
    terrain->prepare(deltaTime);
}

void Scene::physic() 
{
    terrain->physic();
}

void Scene::collisionsCheck() 
{
    terrain->collisionsCheck();
}

void Scene::update()
{
    skybox->update();
    terrain->update();
}

void Scene::lateUpdate() 
{
    terrain->lateUpdate();
}

void Scene::draw(sc::CameraController const& camCtrl, sc::Lights const& lights) 
{
    skybox->draw(camCtrl, sc::Lights{}, scmath::Mat4::identity());
    terrain->draw(camCtrl, lights, scmath::Mat4::identity());
}

void Scene::destroyCheck() 
{
    terrain->destroyCheck();
}

void Scene::createTargets(std::shared_ptr<sc::SCObject> object, sc::AssetsContainer &assets) 
{
    int numberOfTargets = 100;
    float distBetweenTargets = 3.0f;

    scmath::Vec3 basePos(-20.0f, 5.0f, -20.0f);
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