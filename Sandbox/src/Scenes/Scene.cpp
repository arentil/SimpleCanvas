#include "Scene.h"

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
    rootObject->draw(camera, lights);
}
