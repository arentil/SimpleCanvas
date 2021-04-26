#include "Teapot.h"

#include <vector>

Teapot::Teapot(sc::Shader const& shader) 
: sc::SCObject("Teapot", shader)
{
    _model = sc::ObjLoader::loadObjFromFile("assets/models/teapot/teapot.obj");
}

void Teapot::onAnimate(float deltaTime) 
{
    rotationTriangle += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
    _modelMatrix = scmath::Mat4::translate(-2.0f, 0.0f, 2.0f) * 
        scmath::Mat4::rotateY(rotationTriangle) *
        scmath::Mat4::scale(0.01f, 0.01f, 0.01f);
}