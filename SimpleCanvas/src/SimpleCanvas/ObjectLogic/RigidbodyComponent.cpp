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
        addForce(scmath::Vec3::Down() * GRAVITY);

    scmath::Vec3 acceleration = Forces / Mass;
    Velocity += acceleration * deltaTime;
    objectPosition += Velocity * deltaTime;

    IsGrounded = false;
    Forces = scmath::Vec3::Zero();
}

std::pair<bool, CollisionSide> RigidbodyComponent::getCollision(RigidbodyComponent const& other) const
{
    return collider.getCollision(other.collider);
}

void RigidbodyComponent::setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max)
{
    collider.bb.setMinMax(min, max);
}

void RigidbodyComponent::addForce(scmath::Vec3 const& force) 
{
    Forces += force;
}
} // namespace sc