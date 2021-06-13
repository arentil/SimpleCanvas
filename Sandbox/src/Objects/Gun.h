#pragma once

#include "SimpleCanvas.h"

class Gun : public sc::SCObject
{
public:
    Gun(sc::AssetsContainer const& assets);

    void shoot();

private:
    sc::AssetsContainer const& assetsC;
    bool createProjectile = false;
    float timeSinceLastShoot = 1.0f;
    float fireRate = 600.0f / 60.0f;    // rounds per second
    int timesToReturn = 0;
    bool needToReturn = false;

    virtual void onPrepare() override;
    virtual void onUpdate() override;
};