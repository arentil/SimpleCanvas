#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox : public sc::SCObject
{
public:
    Skybox(sc::AssetsContainer const& assets, sc::FPSCamera const& camera);

    void onAnimate(float deltaTime) override;
    void onDraw(sc::FPSCamera const& camera, sc::Lights const& lights, scmath::Mat4 const& modelMatrix) override;

private:
    sc::TexturePtr cubemap;
    sc::FPSCamera const& _camera;
};