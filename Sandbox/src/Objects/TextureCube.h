#pragma once

#include "SimpleCanvas.h"

#include <memory>

class TextureCube : public sc::SCObject
{
public:
    TextureCube(sc::AssetsContainer const& assets);

    virtual void onAnimate(float deltaTime) override;
};