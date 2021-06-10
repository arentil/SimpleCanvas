#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Player : public sc::SCObject
{
public:
    Player(sc::AssetsContainer const& assets, sc::CameraController & camCtrl);

    virtual void onCollision(SCObject *collisionObject) override;
    virtual void updateCollider() override;
    virtual void onLateUpdate() override;

private:
    sc::CameraController & cam;
    scmath::Vec3 min;
    scmath::Vec3 max;
};