#pragma once

#include "SimpleCanvas.h"

#include <memory>

class ColorCube
{
public:
    ColorCube(sc::Shader const& shader, sc::Camera const& camera);

    void draw(sc::Lights const& material, scmath::Mat4 const& modelMatrix) const;

private:
    sc::Shader const& _shader;
    sc::Camera const& _camera;
    sc::ModelPtr _model;
};