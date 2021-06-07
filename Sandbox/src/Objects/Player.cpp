#include "Player.h"

Player::Player(sc::AssetsContainer const& assets, sc::FPSCamera & cam)
:  sc::SCObject("Player", assets.Shaders.getShader("FlatColor"))
, camera(cam)
, min(-0.5f, -0.5f, -0.5f)
, max(0.5f, 0.5f, 0.5f)
{
    _model = std::make_shared<sc::Model>();
    Collider.emplace(min, max);
    Collider->initDebugShader();
}

void Player::onCollision(SCObject *collisionObject) 
{
    LOG_ERROR("Collision %s with %s", Name.c_str(), collisionObject->Name.c_str());
}

void Player::updateCollider() 
{
    Collider->bb.setMinMax(min + camera._position, max + camera._position);
}

