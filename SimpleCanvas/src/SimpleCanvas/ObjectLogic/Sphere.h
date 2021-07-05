#pragma once

#include <SCMath.h>

namespace sc
{
class Sphere
{
public:
    Sphere() = default;
    Sphere(scmath::Vec3 const& centerPoint, float sphereRadius);

    bool isCollision(Sphere const& other) const;

    scmath::Vec3 center;
    float radius;
};
} // namespace sc