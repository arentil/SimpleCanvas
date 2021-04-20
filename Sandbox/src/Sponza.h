#pragma once

#include "SimpleCanvas.h"

#include <memory>

class Sponza
{
public:
    Sponza(sc::Shader const& shader, sc::Camera const& camera);

    void draw(scmath::Mat4 const& modelMatrix) const;

private:
    sc::Shader const& _shader;
    sc::Camera const& _camera;
    sc::Model _model;
};