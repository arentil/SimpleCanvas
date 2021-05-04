#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Triangle : public sc::SCObject
{
public:
    Triangle(sc::AssetsContainer const& assets);
    virtual ~Triangle() = default;

    void onAnimate(float deltaTime) override;

private:
	float rotationTriangle = 0.0f;
	float rotationTriangleSpeed = 30.0f;
    scmath::Vec3 rotateAxis{0.0f, 0.0f, 1.0f};
};