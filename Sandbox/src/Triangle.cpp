#include "Triangle.h"

#include <vector>

Triangle::Triangle(sc::Shader const& shader, sc::Camera const& camera) 
: _shader(shader)
, _camera(camera)
{
    std::vector<sc::ColorVertex> const vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}
    };

    auto mesh = std::make_shared<sc::ColorMesh>(vertices);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void Triangle::draw(sc::Material const& material, scmath::Mat4 const& modelMatrix) const
{
    _model->draw(_shader, _camera, material, modelMatrix);
}