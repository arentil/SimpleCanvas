#pragma once

#include "SimpleCanvas.h"

class Target : public sc::SCObject
{
public:
    Target(sc::AssetsContainer const& assets);

    void onCollision(SCObject *object, sc::CollisionDir direction) override;

    float scale = 1.0f;
    static int count;
};