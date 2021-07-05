#pragma once

#include "SimpleCanvas.h"
#include "Gun.h"

#include <memory>

class Player : public sc::SCObject
{
public:
    Player(sc::AssetsContainer const& assets, sc::CameraController & camCtrl);

    virtual void onCollision(sc::SCObject *collisionObject, sc::CollisionSide side) override;
    virtual void updateCollider() override;
    virtual void onUpdate() override;
    virtual void onLateUpdate() override;

private:
    sc::CameraController & cam;
    scmath::Vec3 min;
    scmath::Vec3 max;

    scmath::Vec3 const initialPosition = scmath::Vec3(0.0f, 3.0f, 3.0f);
    float terrainBounceModifier = 0.1f;
};