#include "RotatingTarget.h"

RotatingTarget::RotatingTarget(sc::AssetsContainer const& assets) 
: sc::SCObject("RotatingTarget", assets.Shaders.getShader("Color"))
{
    _model = assets.Models.getModel("Cube");
    Rigidbody.emplace();
    Transform.Translation.x = -10.0f;
    Transform.Translation.y = 0.0f;
    Transform.Translation.z = -25.0f;
}

void RotatingTarget::onUpdate() 
{
    Transform.Translation.y += std::sin(sinX) * 0.2f;
    Transform.Translation.z += std::cos(cosX) * 0.2f;
    sinX += 0.05f;
    cosX += 0.05f;
}