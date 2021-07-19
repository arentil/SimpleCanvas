#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Terrain : public sc::SCObject
{
public:
    Terrain(sc::AssetsContainer const& assets);
    virtual ~Terrain() = default;
};