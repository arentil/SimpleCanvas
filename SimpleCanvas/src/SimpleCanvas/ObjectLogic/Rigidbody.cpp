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

    objectPosition += Velocity * deltaTime;
    Velocity += Acceleration * deltaTime;
}

bool Rigidbody::isCollision(Rigidbody const& other) const
{
    return Collider.isCollision(other.Collider);
}

void Rigidbody::setColliderMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max) 
{
    Collider.bb.setMinMax(min, max);
}
} // namespace sc