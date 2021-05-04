#pragma once

#include "SimpleCanvas.h"

#include <memory>

class ColorCube : public sc::SCObject
{
public:
    ColorCube(sc::AssetsContainer const& assets);

    void onAnimate(float deltaTime) override;

public:
    float rotationAngle = 0.0f;
    float rotationSpeed = 30.0f;
    scmath::Vec3 pos{0.5f, 0.0f, 0.0f};
};