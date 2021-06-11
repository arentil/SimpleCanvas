#include "Gun.h"

#include "Player.h"
#include "Projectile.h"

Gun::Gun(sc::AssetsContainer const& assets) 
: sc::SCObject("AK-47", assets.Shaders.getShader("Texture"))
, assetsC(assets)
{
    _model = assets.Models.getModel("AK-47");

    Transform.Translation = scmath::Vec3(0.4f, -0.4f, -0.6f);
    Transform.Rotation.y = scmath::degToRad(180.0f);
    float scale = 0.004f;
    Transform.Scale = scmath::Vec3(scale, scale, scale);
}

void Gun::onPrepare() 
{
    if (createProjectile)
    {
        createProjectile = false;

        Projectile *projectile = new Projectile(assetsC);
        projectile->attachTo(findRoot());

        auto player = getParent();

        // slightly adjust projectile, so it can spawn at the end of the gun
        auto tempGunTransform = Transform;
        tempGunTransform.Translation.x -= 0.0f;
        tempGunTransform.Translation.y += 0.15f;
        tempGunTransform.Translation.z -= 0.5f;
        auto transform = player->Transform.GetTransform() * tempGunTransform.GetTransform();

        projectile->Transform.Translation = transform * projectile->Transform.Translation;
        projectile->Transform.Rotation = player->Transform.Rotation;
    }
}

void Gun::shoot() 
{
    // pojectile will be created in onPrepare()
    createProjectile = true;
}