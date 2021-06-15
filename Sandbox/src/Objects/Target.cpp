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
    std::string str = "";
    switch (direction)
    {
        case sc::CollisionDir::FRONT:
            str = "FRONT";
            break;
        case sc::CollisionDir::BACK:
            str = "BACK";
            break;
        case sc::CollisionDir::TOP:
            str = "TOP";
            break;
        case sc::CollisionDir::BOTTOM:
            str = "BOTTOM";
            break;
        case sc::CollisionDir::LEFT:
            str = "LEFT";
            break;
        case sc::CollisionDir::RIGHT:
            str = "RIGHT";
            break;
    }
    LOG_ERROR("Target collision with %s on %s", object->Name.c_str(), str.c_str());
}