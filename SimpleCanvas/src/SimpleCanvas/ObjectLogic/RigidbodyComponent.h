#pragma once

#include <SCMath.h>

#include "AABB.h"

namespace sc
{
constexpr float GRAVITY = 9.81; // m/s^2

class RigidbodyComponent
{
public:
    RigidbodyComponent() = default;
    RigidbodyComponent(scmath::Vec3 const& min, scmath::Vec3 const& max);    // for aabb collider

    void physic(scmath::Vec3 & objectPosition, float deltaTime);
    std::pair<bool, CollisionSide> getCollision(RigidbodyComponent const& other) const;
    void setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max);
    void addForce(scmath::Vec3 const& force);

    bool IsKinematic = false;

    float Mass = 1.0f;
    scmath::Vec3 Forces = {0.0f, 0.0f, 0.0f};
    scmath::Vec3 Velocity = {0.0f, 0.0f, 0.0f};
    // scmath::Vec3 Acceleration = {0.0f, 0.0f, 0.0f};
    bool IsGrounded = false;

    
    AABB collider;
};
} // namespace sc