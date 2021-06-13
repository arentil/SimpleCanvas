#include "Projectile.h"

Projectile::Projectile(sc::AssetsContainer const& assets) 
: sc::SCObject("Projectile", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("RedSphere");
    //Rigidbody.emplace();
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

void Projectile::updateCollider() 
{
    // scmath::Vec3 min = scmath::Vec3(-0.5f, -0.5f, -0.5f) * scale;
    // scmath::Vec3 max = scmath::Vec3(0.5f, 0.5f, 0.5f) * scale;

    // scmath::Vec3 getGlobalTransform = getParent()->Transform.GetTransform() * Transform.Translation;

    // Rigidbody->setColliderMinMax(getGlobalTransform + min, getGlobalTransform + max);
    //sc::SCObject::updateCollider();
}