#include "PerspectiveCamera.h"

namespace sc
{
PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
: Camera(CameraType::PERSPECTIVE
    , scmath::Mat4::perspective(fov, aspect, near, far)     // E.g: 70.0f, 16.0f / 9.0f, 0.0001f, 10.0f))
    , scmath::Mat4::identity())
{}

void PerspectiveCamera::setProjection(float fov, float aspect, float near, float far)
{
    _projMatrix = scmath::Mat4::perspective(fov, aspect, near, far);
    _viewProjMatrix = _projMatrix * _viewMatrix;
}
} // namespace sc