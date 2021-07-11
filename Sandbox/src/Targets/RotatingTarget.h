#pragma once

#include "SimpleCanvas.h"

class RotatingTarget : public sc::SCObject
{
public:
    RotatingTarget(sc::AssetsContainer const& assets);

    void onUpdate() override;

    float sinX = 0.0f;
    float cosX = 0.0f;
    float moveMultiplier = 0.1f;
};