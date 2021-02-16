#include "OrthoCamera.h"

#include <SCMath.h>

namespace sc
{
OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
//: _projMatrix(scmath::Mat4::ortho(left, right, bottom, top, -1.0f, 1.0f))
: _projMatrix(scmath::Mat4::perspective(70.0f, 16.0f / 9.0f, 0.0001f, 10.0f))
, _viewMatrix(scmath::Mat4::identity())
{
    _viewProjMatrix = _projMatrix * _viewMatrix;
}

void OrthoCamera::recalculateViewMatrix()
{
    scmath::Mat4 transform = scmath::Mat4::translate(_position) * scmath::Mat4::rotate(scmath::degToRad(_rotation), scmath::Vec3(0, 0, 1));
    _viewMatrix = scmath::Mat4::inverse(transform);
    _viewProjMatrix = _projMatrix * _viewMatrix;
}
} // namespace sc