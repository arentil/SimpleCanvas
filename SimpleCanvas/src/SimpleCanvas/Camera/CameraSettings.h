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
    float zoomMin = 20.0f;
    float zoomMax = 120.0f;

    float getAspect() const
    {
        return AspectWidth / AspectHeight;
    }
};
} // namespace sc