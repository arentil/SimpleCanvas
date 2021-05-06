#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Teapot : public sc::SCObject
{
public:
    Teapot(sc::AssetsContainer const& assets);

    void onAnimate(float deltaTime) override;

private:
	float rotationTriangleSpeed = 30.0f;
};