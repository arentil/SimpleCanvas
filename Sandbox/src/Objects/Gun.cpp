#include "Gun.h"

Gun::Gun(sc::AssetsContainer const& assets) 
: sc::SCObject("AK-47", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("AK-47");

    Transform.Translation = scmath::Vec3(0.4f, -0.4f, -0.6f);
    Transform.Rotation.y = scmath::degToRad(180.0f);
    float scale = 0.004f;
    Transform.Scale = scmath::Vec3(scale, scale, scale);
}