#include "Player.h"

Player::Player(sc::AssetsContainer const& assets, sc::CameraController const& camCtrl)
:  sc::SCObject("Player", assets.Shaders.getShader("FlatColor"))
, cam(camCtrl)
, min(-0.5f, -0.5f, -0.5f)
, max(0.5f, 0.5f, 0.5f)
{
    _model = std::make_shared<sc::Model>();
    Rigidbody->setColliderMinMax(min, max);
    Rigidbody->Collider.initDebugShader();
    Transform.Translation = scmath::Vec3(0.0f, 0.0f, 3.0f);
}

void Player::onCollision(SCObject *collisionObject) 
{
    LOG_ERROR("Collision %s with %s", Name.c_str(), collisionObject->Name.c_str());
}

void Player::updateCollider() 
{
    Rigidbody->setColliderMinMax(min + cam.getPosition(), max + cam.getPosition());
}

