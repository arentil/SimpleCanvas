#pragma once

#include <SCMath.h>

#include "AABB.h"

namespace sc
{
constexpr float G = 9.81; // m/s^2

class Rigidbody
{
public:
    Rigidbody() = default;
    Rigidbody(scmath::Vec3 const& min, scmath::Vec3 const& max);    // for aabb collider
    //Rigidbody(scmath::Vec3 const& center, float radius);            // for sphere collider

    void physic(scmath::Vec3 & objectPosition, float deltaTime);
    bool isCollision(Rigidbody const& other) const;
    void setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max);
    void addForce(scmath::Vec3 const& force);

    bool IsKinematic = false;

    float Mass = 1.0f;
    scmath::Vec3 Velocity = {0.0f, 0.0f, 0.0f};
    scmath::Vec3 Acceleration = {0.0f, 0.0f, 0.0f};
    bool IsGrounded = false;
    
    AABB collider;
};
} // namespace sc