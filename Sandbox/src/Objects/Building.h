#pragma once

#include "SimpleCanvas.h"

class Building : public sc::SCObject
{
public:
    Building(sc::AssetsContainer const& assets);

    static int count;
};