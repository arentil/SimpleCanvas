#include "Teapot.h"

#include <vector>

Teapot::Teapot(sc::AssetsContainer const& assets) 
: sc::SCObject("Teapot", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("Teapot");
}

void Teapot::onAnimate(float deltaTime) 
{
    Transform.Translation = scmath::Vec3(-2.0f, 0.0f, 2.0f);
    Transform.Rotation.y += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
    Transform.Scale = scmath::Vec3(0.01f, 0.01f, 0.01f);
}