#pragma once

#include "SimpleCanvas.h"

#include <memory>

class ColorCube : public sc::SCObject
{
public:
    ColorCube(sc::AssetsContainer const& assets);

    void onAnimate(float deltaTime) override;
};