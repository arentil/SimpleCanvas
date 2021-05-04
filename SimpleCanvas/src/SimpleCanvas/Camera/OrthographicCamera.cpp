#include "OrthographicCamera.h"

namespace sc
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
: Camera(CameraType::ORTHOGRAPHIC
    , scmath::Mat4::orthographic(left, right, bottom, top, near, far)
    , scmath::Mat4::identity())
{}

void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float near, float far)
{
    _projMatrix = scmath::Mat4::orthographic(left, right, bottom, top, near, far);
    _viewProjMatrix = _projMatrix * _viewMatrix;
}
} // namespace sc