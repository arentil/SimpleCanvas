#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Triangle : public sc::SCObject
{
public:
    Triangle(sc::AssetsContainer const& assets);
    virtual ~Triangle() = default;

    void onUpdate() override;
};