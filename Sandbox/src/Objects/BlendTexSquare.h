#pragma once

#include "SimpleCanvas.h"

#include <memory>

class BlendTexSquare : public sc::SCObject
{
public:
    BlendTexSquare(sc::Shader const& shader, sc::TexturePtr const texture);
};