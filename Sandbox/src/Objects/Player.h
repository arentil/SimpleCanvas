#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Player : public sc::SCObject
{
public:
    Player(sc::AssetsContainer const& assets, sc::FPSCamera & cam);

    virtual void onCollision(SCObject *collisionObject) override;
    virtual void updateCollider() override;

private:
    sc::FPSCamera const& camera;
    scmath::Vec3 min;
    scmath::Vec3 max;
};