#include "AABBCollider.h"

#include "SphereCollider.h"

namespace sc
{
AABBCollider::AABBCollider()
: Collider(ColliderType::AABB)
{}

AABBCollider::AABBCollider(scmath::Vec3 const& minPoint, scmath::Vec3 const& maxPoint)
: Collider(ColliderType::AABB)
, Min(minPoint)
, Max(maxPoint)
{}

bool AABBCollider::isCollision(Collider const& other) const 
{
    if (other.getType() == ColliderType::AABB)
        return isCollisionWithAABB((AABBCollider const&)other);

    if (other.getType() == ColliderType::SPHERE)
        return isCollisionWithSphere((SphereCollider const&)other);

    return false;
}

bool AABBCollider::isCollisionWithAABB(AABBCollider const& aabb) const
{
    return (Min.x <= aabb.Max.x && Max.x >= aabb.Min.x) &&
           (Min.y <= aabb.Max.y && Max.y >= aabb.Min.y) &&
           (Min.z <= aabb.Max.z && Max.z >= aabb.Min.z);
}

bool AABBCollider::isCollisionWithSphere(SphereCollider const& sphere) const
{
    return sphere.isCollisionWithAABB(*this);
}
} // namespace sc