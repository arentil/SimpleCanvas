#include "HorizontalMovingTarget.h"

HorizontalMovingTarget::HorizontalMovingTarget(sc::AssetsContainer const& assets) 
: sc::SCObject("RotatingTarget", assets.Shaders.getShader("Color"))
{
    _model = assets.Models.getModel("Cube");
    Rigidbody.emplace();
    Transform.Translation.x = -10.0f;
    Transform.Translation.y = 0.0f;
    Transform.Translation.z = -20.0f;
}

void HorizontalMovingTarget::onUpdate() 
{
    sinX += 0.05f;
    Transform.Translation.z += std::sin(sinX) * 0.2f;
}