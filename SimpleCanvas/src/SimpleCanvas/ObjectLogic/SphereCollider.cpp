#include "SphereCollider.h"

#include "AABBCollider.h"

namespace sc
{
SphereCollider::SphereCollider()
: Collider(ColliderType::SPHERE)
{}

SphereCollider::SphereCollider(scmath::Vec3 const& centerPoint, float radiusSize) 
: Collider(ColliderType::SPHERE)
, Center(centerPoint)
, Radius(radiusSize)
{}

bool SphereCollider::isCollision(Collider const& other) const 
{
    if (other.getType() == ColliderType::SPHERE)
        return isCollisionWithSphere((SphereCollider const&)other);

    if (other.getType() == ColliderType::AABB)
        return isCollisionWithAABB((AABBCollider const&)other);

    return false;
}

bool SphereCollider::isCollisionWithSphere(SphereCollider const& sphere) const
{
    return scmath::Vec3::distance(Center, sphere.Center) < (Radius + sphere.Radius);
}

bool SphereCollider::isCollisionWithAABB(AABBCollider const& aabb) const
{
    return squaredDistPointAABB(Center, aabb) <= (Radius * Radius);
}

float SphereCollider::squaredDistPointAABB(scmath::Vec3 const& point, AABBCollider const& aabb) const
{
    auto check = [&](float pn, float bmin, float bmax ) -> float
    {
        float out = 0;
        float v = pn;
 
        if ( v < bmin ) 
        {             
            float val = (bmin - v);             
            out += val * val;         
        }         
         
        if ( v > bmax )
        {
            float val = (v - bmax);
            out += val * val;
        }
 
        return out;
    };
 
    // Squared distance
    float sq = 0.0;
 
    sq += check( point.x, aabb.Min.x, aabb.Max.x );
    sq += check( point.y, aabb.Min.y, aabb.Max.y );
    sq += check( point.z, aabb.Min.z, aabb.Max.z );
 
    return sq;
}
}