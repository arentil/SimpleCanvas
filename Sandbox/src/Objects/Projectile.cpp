#include "Projectile.h"

Projectile::Projectile(sc::AssetsContainer const& assets) 
: sc::SCObject("Projectile", assets.Shaders.getShader("FlatColor"))
{
    _model = assets.Models.getModel("Projectile");
    Transform.Scale = Transform.Scale * scale;
}

void Projectile::onUpdate() 
{
    Transform.Translation += Transform.Front() * speed;
}