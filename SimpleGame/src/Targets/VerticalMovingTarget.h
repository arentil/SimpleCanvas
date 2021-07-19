#pragma once

#include "SimpleCanvas.h"

class VerticalMovingTarget : public sc::SCObject
{
public:
    VerticalMovingTarget(sc::AssetsContainer const& assets);

    void onUpdate() override;

    float sinX = 0.0f;
    float moveMultiplier = 0.1f;
};