#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Player : public sc::SCObject
{
public:
    Player(sc::AssetsContainer const& assets, sc::CameraController const& camCtrl);

    virtual void onCollision(SCObject *collisionObject) override;
    virtual void updateCollider() override;

private:
    sc::CameraController const& cam;
    scmath::Vec3 min;
    scmath::Vec3 max;
};