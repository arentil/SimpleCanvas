#pragma once

#include <SCMath.h>

#include "Collider.h"

namespace sc
{
class AABBCollider;

class SphereCollider : public Collider
{
public:
    SphereCollider();
    SphereCollider(scmath::Vec3 const& centerPoint, float radiusSize);

    virtual bool isCollision(Collider const& other) const override;
    bool isCollisionWithSphere(SphereCollider const& sphere) const;
    bool isCollisionWithAABB(AABBCollider const& aabb) const;

    scmath::Vec3 Center;
    float Radius;

private:
    float squaredDistPointAABB(scmath::Vec3 const& point, AABBCollider const& aabb) const;
};
} // namespace sc