#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Terrain : public sc::SCObject
{
public:
    Terrain(sc::Shader const& shader);
    virtual ~Terrain() = default;
};