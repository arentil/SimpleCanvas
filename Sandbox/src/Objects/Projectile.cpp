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
    if (object->Name.find("Player") != std::string::npos)
        return;

    LOG_ERROR("Projectile hit %s", object->Name.c_str());
    destroy();
}