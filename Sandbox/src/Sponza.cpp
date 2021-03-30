#include "Sponza.h"

#include <vector>

Sponza::Sponza(sc::Shader const& shader, sc::Camera const& camera) 
: _shader(shader)
, _camera(camera)
, _model(_objLoader.loadObjFromFile("assets/models/sponza/sponza.obj"))
{
}

void Sponza::draw(scmath::Mat4 const& modelMatrix) const
{
    _model.draw(_shader, _camera, modelMatrix);
}