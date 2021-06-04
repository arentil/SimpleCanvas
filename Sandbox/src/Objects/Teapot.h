#pragma once

#include "SimpleCanvas.h"

class Teapot : public sc::SCObject
{
public:
    Teapot(sc::AssetsContainer const& assets);

    void onAnimate(float deltaTime) override;

private:
	float rotationAngle = 30.0f;
};