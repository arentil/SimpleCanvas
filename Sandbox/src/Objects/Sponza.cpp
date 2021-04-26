#include "Sponza.h"

Sponza::Sponza(sc::Shader const& shader) 
: sc::SCObject("Sponza", shader)
{
    _model = sc::ObjLoader::loadObjFromFile("assets/models/sponza/sponza.obj");
    _modelMatrix = scmath::Mat4::translate(0.0f, -1.0f, 0.0f) * scmath::Mat4::scale(0.01f, 0.01f, 0.01f);
}