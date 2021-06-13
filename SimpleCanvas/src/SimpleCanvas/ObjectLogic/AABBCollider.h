#pragma once

#include <SCMath.h>

#include "Collider.h"

namespace sc
{
class SphereCollider;

class AABBCollider : public Collider
{
public:
    AABBCollider();
    AABBCollider(scmath::Vec3 const& minPoint, scmath::Vec3 const& maxPoint);

    virtual bool isCollision(Collider const& other) const override;
    bool isCollisionWithAABB(AABBCollider const& aabb) const;
    bool isCollisionWithSphere(SphereCollider const& sphere) const;

    scmath::Vec3 Min;
    scmath::Vec3 Max;
};
} // namespace sc