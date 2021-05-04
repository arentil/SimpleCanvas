#pragma once

#include "SimpleCanvas.h"

#include <memory>

class TileMap : public sc::SCObject
{
public:
    TileMap(sc::AssetsContainer const& assets);
};