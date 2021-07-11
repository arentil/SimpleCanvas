#include "VerticalMovingTarget.h"

VerticalMovingTarget::VerticalMovingTarget(sc::AssetsContainer const& assets) 
: sc::SCObject("RotatingTarget", assets.Shaders.getShader("Color"))
{
    _model = assets.Models.getModel("Cube");
    Rigidbody.emplace();
    Transform.Translation.x = -10.0f;
    Transform.Translation.y = 0.0f;
    Transform.Translation.z = -10.0f;
}

void VerticalMovingTarget::onUpdate() 
{
    sinX += 0.05f;
    Transform.Translation.y += std::sin(sinX) * 0.2f;
}