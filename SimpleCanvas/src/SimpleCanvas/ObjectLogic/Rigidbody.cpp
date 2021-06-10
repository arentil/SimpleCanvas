#include "Rigidbody.h"

namespace sc
{
Rigidbody::Rigidbody(scmath::Vec3 const& aabbMin, scmath::Vec3 const& aabbMax)
: Collider(aabbMin, aabbMax)
{}

void Rigidbody::physic(scmath::Vec3 & objectPosition, float deltaTime)
{
    if (!IsKinematic)
        return;

    if (!IsGrounded)
        Acceleration += scmath::Vec3::Down() * G * Mass * deltaTime;

    Velocity += Acceleration;
    objectPosition += Velocity * deltaTime;

    IsGrounded = false;
    Acceleration = scmath::Vec3(0.0f, 0.0f, 0.0f);
}

bool Rigidbody::isCollision(Rigidbody const& other) const
{
    return Collider.isCollision(other.Collider);
}

void Rigidbody::setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max)
{
    Collider.bb.setMinMax(min, max);
}

void Rigidbody::addForce(scmath::Vec3 const& force) 
{
    Acceleration += force / Mass;
}
} // namespace sc