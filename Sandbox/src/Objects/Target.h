#pragma once

#include "SimpleCanvas.h"

class Target : public sc::SCObject
{
public:
    Target(sc::AssetsContainer const& assets);

    float scale = 1.0f;
    static int count;
};