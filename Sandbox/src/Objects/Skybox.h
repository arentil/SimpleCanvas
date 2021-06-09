#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Skybox : public sc::SCObject
{
public:
    Skybox(sc::AssetsContainer const& assets, sc::CameraController const& camCtrl);

    void onUpdate() override;
    void onDraw(sc::CameraController const& camCtrl, sc::Lights const& lights, scmath::Mat4 const& modelMatrix) override;

private:
    sc::TexturePtr cubemap;
    sc::CameraController const& cam;
};