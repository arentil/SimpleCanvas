#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox : public sc::SCObject
{
public:
    Skybox(sc::Shader const& shader);

    void draw(sc::Camera const& camera, sc::Lights const& lights) override;

private:
    sc::TexturePtr cubemap;
};