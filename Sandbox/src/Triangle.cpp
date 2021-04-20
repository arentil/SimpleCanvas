#include "Triangle.h"

#include <vector>

Triangle::Triangle(sc::Shader const& shader, sc::Camera const& camera) 
: _shader(shader)
, _camera(camera)
{
}

void Triangle::draw(scmath::Mat4 const& modelMatrix) const
{
    //_model->draw(_shader, _camera, modelMatrix);
}