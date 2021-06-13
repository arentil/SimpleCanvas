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
    Transform.Translation += Transform.Front() * speed;

    if (Transform.Translation.distance(scmath::Vec3::Zero()) > 50.0f)
        destroy();
}

void Projectile::onCollision(SCObject *object) 
{
    destroy();
}