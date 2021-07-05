#include "Sphere.h"

namespace sc
{
Sphere::Sphere(scmath::Vec3 const& centerPoint, float sphereRadius)
: center(centerPoint)
, radius(sphereRadius)
{
    
}

bool Sphere::isCollision(Sphere const& other) const
{
    return center.distance(other.center) <= radius + other.radius;
}
} // namespace sc