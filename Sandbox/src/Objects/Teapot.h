#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Teapot : public sc::SCObject
{
public:
    Teapot(sc::Shader const& shader);

    void onAnimate(float deltaTime) override;

private:
	float rotationTriangle = 0.0f;
	float rotationTriangleSpeed = 30.0f;
    scmath::Vec3 rotationAxis{0.0f, 1.0f, 0.0f};
};