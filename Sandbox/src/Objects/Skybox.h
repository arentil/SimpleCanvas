#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox : public sc::SCObject
{
public:
    Skybox(sc::AssetsContainer const& assets);

    void draw(sc::FPSCamera const& camera, sc::Lights const& lights) override;

private:
    sc::TexturePtr cubemap;
};