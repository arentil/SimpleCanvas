#pragma once

#include "SimpleCanvas.h"

class Crosshair : public sc::SCObject
{
public:
    Crosshair(sc::AssetsContainer const& assets);

    void onDraw(sc::CameraController const& camCtrl, sc::Lights const& , scmath::Mat4 const& modelMatrix) override;

    uint32_t VAO;
    int verticesCount;
};