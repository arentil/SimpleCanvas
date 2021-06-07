#pragma once

#include <SCMath.h>

#include "AABB.h"

namespace sc
{
class Rigidbody
{
public:
    Rigidbody() = default;
    Rigidbody(scmath::Vec3 const& aabbMin, scmath::Vec3 const& aabbMax);

    AABB aabb;
};
} // namespace sc