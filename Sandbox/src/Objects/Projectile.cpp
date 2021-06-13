#include "Projectile.h"

Projectile::Projectile(sc::AssetsContainer const& assets) 
: sc::SCObject("Projectile", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("RedSphere");
    LOG_ERROR("pointer: %p", &(*(_model.get())));
    Rigidbody.emplace();
    Transform.Scale = Transform.Scale * scale;
}

void Projectile::onUpdate() 
{
    Transform.Translation += Transform.Front() * speed;
}

void Projectile::onCollision(SCObject *object) 
{
    //LOG_WARNING("Projectile collision with %s", object->Name.c_str());
    //IsDead = true;
}