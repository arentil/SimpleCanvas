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

    if (Transform.Translation.distance(scmath::Vec3::Zero()) > maxDist)
        destroy();
}

void Projectile::onCollision(sc::SCObject *object, sc::CollisionSide side) 
{
    if ((object->Name.find("Player") != std::string::npos))
        return;
    
    if ((object->Name.find("Target") != std::string::npos))
        object->destroy();

    destroy();
}