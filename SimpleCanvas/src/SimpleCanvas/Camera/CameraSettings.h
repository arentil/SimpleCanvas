#pragma once

#include <SCMath.h>

namespace sc
{
struct CameraSettings
{
    float Fov;
    float AspectWidth;
    float AspectHeight;
    float Near;
    float Far;

    float getAspect() const
    {
        return AspectWidth / AspectHeight;
    }
};
} // namespace sc