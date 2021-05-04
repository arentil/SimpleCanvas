#pragma once

#include "Camera.h"

namespace sc
{
class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

    void setProjection(float left, float right, float bottom, float top, float near, float far);
};
} // namespace sc