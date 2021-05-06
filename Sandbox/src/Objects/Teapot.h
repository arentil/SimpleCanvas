#pragma once

#include "SimpleCanvas.h"

class Teapot : public sc::SCObject
{
public:
    Teapot(sc::AssetsContainer const& assets);

    void onAnimate(float deltaTime) override;

private:
	float rotationSpeed = 30.0f;
};