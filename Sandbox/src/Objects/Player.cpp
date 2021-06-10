#include "Player.h"

Player::Player(sc::AssetsContainer const& assets, sc::CameraController & camCtrl)
:  sc::SCObject("Player", assets.Shaders.getShader("FlatColor"))
, cam(camCtrl)
, min(-0.5f, -0.5f, -0.5f)
, max(0.5f, 0.5f, 0.5f)
{
    _model = std::make_shared<sc::Model>();
    
    if (!Rigidbody.has_value())
        Rigidbody.emplace();
    Rigidbody->setColliderMinMax(min, max);
    Rigidbody->Collider.initDebugShader();
    Rigidbody->IsKinematic = true;

    Transform.Translation = scmath::Vec3(0.0f, 4.0f, 3.0f);
}

void Player::onCollision(SCObject *collisionObject) 
{
    if (collisionObject->Name != "Terrain")
        return;
    Rigidbody->IsGrounded = true;
    // set negative velocity.y so that player can stay on terrain
    Rigidbody->Velocity.y = -(Rigidbody->Velocity.y) * terrainBounceModifier;
}

void Player::updateCollider() 
{
    Rigidbody->setColliderMinMax(min + cam.getPosition(), max + cam.getPosition());
}

void Player::onLateUpdate() 
{
    cam.setPosition(Transform.Translation);
}

