#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Teapot
{
public:
    Teapot(sc::Shader const& shader, sc::Camera const& camera);

    void draw(scmath::Mat4 const& modelMatrix) const;

private:
    sc::Shader const& _shader;
    sc::Camera const& _camera;
    sc::ObjLoader _objLoader;
    sc::Model _model;
};