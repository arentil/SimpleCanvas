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

    scmath::Vec3 forces = scmath::Vec3(0.0f, -1.0f, 0.0f) * G;

    float mass = 100.0f;
    scmath::Vec3 acc = forces / mass;
    Velocity += acc * deltaTime;
    objectPosition += Velocity * deltaTime;
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