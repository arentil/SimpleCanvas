#pragma once

#include "SimpleCanvas.h"

#include <memory>

class TextureCube : public sc::SCObject
{
public:
    TextureCube(sc::AssetsContainer const& assets);

    virtual void onUpdate() override;

private:
    float theta = 0.0f;
};