#pragma once

#include <SCMath.h>

namespace sc
{
struct Plane
{
    Plane() = default;
    Plane(scmath::Vec3 const& p0, scmath::Vec3 const& p1, scmath::Vec3 const& p2);

    void setPoints(scmath::Vec3 const& p0, scmath::Vec3 const& p1, scmath::Vec3 const& p2);
    float distance(scmath::Vec3 const& point) const;
    scmath::Vec3 projectToPlane(scmath::Vec3 const& point) const;

    scmath::Vec3 v, u, normal;
    float D;
};
} // namespace sc