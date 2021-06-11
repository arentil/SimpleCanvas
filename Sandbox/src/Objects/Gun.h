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

    virtual void onPrepare() override;
};