#include "RigidbodyComponent.h"

namespace sc
{
RigidbodyComponent::RigidbodyComponent(scmath::Vec3 const& aabbMin, scmath::Vec3 const& aabbMax)
: collider(aabbMin, aabbMax)
{}

void RigidbodyComponent::physic(scmath::Vec3 & objectPosition, float deltaTime)
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

bool RigidbodyComponent::isCollision(RigidbodyComponent const& other) const
{
    return collider.isCollision(other.collider);
}

void RigidbodyComponent::setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max)
{
    collider.bb.setMinMax(min, max);
}

void RigidbodyComponent::addForce(scmath::Vec3 const& force) 
{
    Acceleration += force / Mass;
}
} // namespace sc