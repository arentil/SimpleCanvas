#pragma once

#include "SimpleCanvas.h"

class Projectile : public sc::SCObject
{
public:
    Projectile(sc::AssetsContainer const& assets);

    virtual void onUpdate() override;

    float speed = 0.1f;
    float scale = 0.1f;
};