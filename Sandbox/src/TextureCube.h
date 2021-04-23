#pragma once

#include "SimpleCanvas.h"

#include <memory>

class TextureCube
{
public:
    TextureCube(sc::Shader const& shader, sc::Camera const& camera, sc::Texture2dPtr const texture);

    void draw(scmath::Mat4 const& modelMatrix) const;

private:
    sc::Shader const& _shader;
    sc::Camera const& _camera;
    std::shared_ptr<sc::Model> _model;
};