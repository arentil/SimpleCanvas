#pragma once

#include "Camera.h"

namespace sc
{
class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fov, float aspect, float near, float far);

    void setProjection(float fov, float aspect, float near, float far);
};
} // namespace sc