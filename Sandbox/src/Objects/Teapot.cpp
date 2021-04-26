#include "Teapot.h"

#include <vector>

Teapot::Teapot(sc::Shader const& shader, sc::Camera const& camera) 
: _shader(shader)
, _camera(camera)
, _model(sc::ObjLoader::loadObjFromFile("assets/models/teapot/teapot.obj"))
{
}

void Teapot::draw(sc::Lights const& material, scmath::Mat4 const& modelMatrix) const
{
    _model.draw(_shader, _camera, material, modelMatrix);
}