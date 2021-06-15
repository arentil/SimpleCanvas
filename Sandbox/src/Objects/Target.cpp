#include "Target.h"

int Target::count = 0;

Target::Target(sc::AssetsContainer const& assets) 
: sc::SCObject("Target" + std::to_string(count++), assets.Shaders.getShader("Color"))
{
    _model = assets.Models.getModel("Cube");
    Rigidbody.emplace();
    Transform.Scale = Transform.Scale * scale;
    Transform.Translation.y = 5.0f;
}

void Target::onCollision(SCObject *object, sc::CollisionDir direction) 
{
    if (object->Name.find("Projectile") != std::string::npos)
        destroy();
}