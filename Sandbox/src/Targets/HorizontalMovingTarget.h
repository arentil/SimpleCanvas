#pragma once

#include "SimpleCanvas.h"

class HorizontalMovingTarget : public sc::SCObject
{
public:
    HorizontalMovingTarget(sc::AssetsContainer const& assets);

    void onUpdate() override;

    float sinX = 0.0f;
    float moveMultiplier = 0.1f;
};