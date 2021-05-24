#include "Teapot.h"

Teapot::Teapot(sc::AssetsContainer const& assets) 
: sc::SCObject("Teapot", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("Teapot");

    Transform.Translation = scmath::Vec3(-2.0f, 0.0f, 2.0f);
    Transform.Scale = scmath::Vec3(0.01f, 0.01f, 0.01f);
}

void Teapot::onAnimate(float deltaTime) 
{
    Transform.Rotation.x += scmath::degToRad(rotationAngle) * deltaTime;
    Transform.Rotation.y += scmath::degToRad(rotationAngle) * deltaTime;
    Transform.Rotation.z += scmath::degToRad(rotationAngle) * deltaTime;
}