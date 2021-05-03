#pragma once

#include <SCMath.h>

#include "Renderer/Camera.h"

namespace sc
{
class AABB
{
public:
    AABB() = default;
    AABB(scmath::Vec3 const& min, scmath::Vec3 const& max);
    virtual ~AABB() = default;

    void setMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max);
    bool isInFrustrum(Camera const& camera, scmath::Mat4 const& modelMatrix) const;

    scmath::Vec3 _min;
    scmath::Vec3 _max;
};
} // namespace sc