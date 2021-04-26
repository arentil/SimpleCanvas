#pragma once

#include "SimpleCanvas.h"

#include <memory>

class TextureCube : public sc::SCObject
{
public:
    TextureCube(sc::Shader const& shader, sc::TexturePtr const texture);
};