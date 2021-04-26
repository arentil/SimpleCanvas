#pragma once

#include "SimpleCanvas.h"

#include <memory>

class TileMap
{
public:
    TileMap(sc::Shader const& shader, sc::Camera const& camera);

    void draw(sc::Lights const& material, scmath::Mat4 const& modelMatrix = scmath::Mat4::identity()) const;

private:
    sc::Shader const& _shader;
    sc::Camera const& _camera;
    std::shared_ptr<sc::Model> _model;
};