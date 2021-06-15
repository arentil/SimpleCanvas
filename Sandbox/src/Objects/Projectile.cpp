#include "Projectile.h"

Projectile::Projectile(sc::AssetsContainer const& assets) 
: sc::SCObject("Projectile", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("RedSphere");
    Rigidbody.emplace();
    Transform.Scale = Transform.Scale * scale;
}

void Projectile::onUpdate() 
{
    Transform.Translation += Transform.Front() * speed * deltaTime;

    if (Transform.Translation.distance(scmath::Vec3::Zero()) > 50.0f)
        destroy();
}

void Projectile::onCollision(sc::SCObject *object, sc::CollisionDir direction) 
{
    // if (object->Name.find("Target") != std::string::npos)
    //     object->destroy();
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
    LOG_ERROR("Projectile collision with %s on %s", object->Name.c_str(), str.c_str());
    destroy();
}