#pragma once

#include "SimpleCanvas.h"

class Projectile : public sc::SCObject
{
public:
    Projectile(sc::AssetsContainer const& assets);

    virtual void onUpdate() override;
    virtual void onCollision(SCObject *object) override;
    virtual void updateCollider();

    float speed = 0.01f;
    float scale = 0.1f;
};