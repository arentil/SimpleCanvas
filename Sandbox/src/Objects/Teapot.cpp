#include "Teapot.h"

#include <vector>

Teapot::Teapot(sc::AssetsContainer const& assets) 
: sc::SCObject("Teapot", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("Teapot");
}

void Teapot::onAnimate(float deltaTime) 
{
    rotationTriangle += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
    _modelMatrix = scmath::Mat4::translate(-2.0f, 0.0f, 2.0f) * 
        scmath::Mat4::rotateY(rotationTriangle) *
        scmath::Mat4::scale(0.01f, 0.01f, 0.01f);
}