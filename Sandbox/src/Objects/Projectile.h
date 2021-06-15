#pragma once

#include "SimpleCanvas.h"

class Projectile : public sc::SCObject
{
public:
    Projectile(sc::AssetsContainer const& assets);

    virtual void onUpdate() override;
    virtual void onCollision(sc::SCObject *object, sc::CollisionDir direction) override;

    float speed = 10.0f;
    float scale = 0.05f;
};