#include "Player.h"

Player::Player(sc::AssetsContainer const& assets, sc::CameraController & camCtrl)
:  sc::SCObject("Player", assets.Shaders.getShader("Color"))
, cam(camCtrl)
, min(-0.5f, -1.0f, -0.5f)
, max(0.5f, 0.5f, 0.5f)
{
    _model = std::make_shared<sc::Model>();
    
    if (!Rigidbody.has_value())
        Rigidbody.emplace();
    Rigidbody->setColliderMinMax(min, max);
    Rigidbody->collider.initDebugShader();
    Rigidbody->IsKinematic = true;

    Transform.Translation = initialPosition;
}

void Player::onCollision(sc::SCObject *collisionObject, sc::CollisionSide side) 
{
    if (collisionObject->Name != "Terrain" && collisionObject->Name.find("Target") == std::string::npos)
        return;

    if (side == sc::CollisionSide::DOWN)
    {
        Rigidbody->IsGrounded = true;
        // set negative velocity.y so that player can stay on terrai
        Rigidbody->Velocity.y = -(Rigidbody->Velocity.y) * terrainBounceModifier;
        return;
    }

    if  (side == sc::CollisionSide::LEFT || side == sc::CollisionSide::RIGHT)
        Transform.Translation.x = cam.lastPosition.x;
    else if (side == sc::CollisionSide::FRONT || side == sc::CollisionSide::BACK)
        Transform.Translation.z = cam.lastPosition.z;
}

void Player::updateCollider() 
{
    Rigidbody->setColliderMinMax(min + cam.getPosition(), max + cam.getPosition());
}

void Player::onUpdate() 
{
    if (sc::Input::isMousePressed(sc::BUTTON_LEFT))
    {
        auto gun = (Gun*)(findChildByName("AK-47"));
        gun->shoot();
    }

    if (Transform.Translation.y < -2.0f)
    {
        Rigidbody->Acceleration = scmath::Vec3::Zero();
        Rigidbody->Velocity = scmath::Vec3::Zero();
        Transform.Translation = initialPosition;
    }

    // this is for propagate rotation of player to child(gun)
    Transform.Rotation.x = scmath::degToRad(cam.pitch);
    Transform.Rotation.y = -scmath::degToRad(cam.yaw + 90.0f);
}

void Player::onLateUpdate() 
{
    cam.setPosition(Transform.Translation);
}