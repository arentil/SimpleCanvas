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
        scmath::Vec3 rotationAdjust(0.003f, 0.01f, 0.0f);
        projectile->Transform.Rotation = player->Transform.Rotation + rotationAdjust;
    }
}

void Gun::onUpdate() 
{
    // animate!
    float timeBetweenShots = 1.0f / fireRate;
    if (timeSinceLastShoot < (timeBetweenShots / 2.0f))
    {
        
        Transform.Translation.z += 0.02f;
        timesToReturn++;
    }
    else
    {
        if (timesToReturn != 0)
        {
            Transform.Translation.z -= 0.02f;
            timesToReturn--;
        }
    }
    Transform.Translation.z = std::clamp(Transform.Translation.z, -0.6f, 0.30f);

    timeSinceLastShoot += deltaTime;
}

void Gun::shoot() 
{
    if (timeSinceLastShoot > (1.0f / fireRate))
    {
        createProjectile = true;
        timeSinceLastShoot = 0.0f;
    }
}