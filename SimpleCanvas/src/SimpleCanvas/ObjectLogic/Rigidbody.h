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
    Rigidbody(scmath::Vec3 const& min, scmath::Vec3 const& max);

    void physic(scmath::Vec3 & objectPosition, float deltaTime);
    bool isCollision(Rigidbody const& other) const;

    void setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max);

    float Mass = 100.0f;
    scmath::Vec3 Velocity;
    scmath::Vec3 Acceleration;
    bool IsKinematic = false;
    AABB Collider;
};
} // namespace sc