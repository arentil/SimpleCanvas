#include "Plane.h"

namespace sc
{
Plane::Plane(scmath::Vec3 const& p0, scmath::Vec3 const& p1, scmath::Vec3 const& p2) 
{
    setPoints(p0, p1, p2);
}

void Plane::setPoints(scmath::Vec3 const& p0, scmath::Vec3 const& p1, scmath::Vec3 const& p2) 
{
    v = p1 - p0;
    u = p2 - p0;
    normal = v.cross(u).normalized();
    D = -normal.dot(p0);
}

float Plane::distance(scmath::Vec3 const& point) const
{
    return normal.dot(point) + D;
}

scmath::Vec3 Plane::projectToPlane(scmath::Vec3 const& point) const
{
    return point - (distance(point) * normal);
}
} // namespace sc