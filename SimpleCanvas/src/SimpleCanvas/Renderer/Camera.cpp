#include "Camera.h"

namespace sc
{
Camera::Camera(CameraType type, scmath::Mat4 const& projectionMatrix, scmath::Mat4 const& viewMatrix)
: _type(type)
, _projMatrix(projectionMatrix)
, _viewMatrix(viewMatrix)
{
    _viewProjMatrix = _projMatrix * _viewMatrix;
}

CameraType Camera::getType() const
{
    return _type;
}

void Camera::setPosition(scmath::Vec3 const& position) 
{
     _position = position; 
     recalculateViewMatrix(); 
}

scmath::Vec3 Camera::getPosition() const
{ 
    return _position;
}

void Camera::setRotation(float rotation) 
{
    _rotation = rotation;
    recalculateViewMatrix(); 
}

float Camera::getRotation() const 
{ 
    return _rotation; 
}

const scmath::Mat4& Camera::getProjMatrix() const 
{ 
    return _projMatrix; 
}

const scmath::Mat4& Camera::getViewMatrix() const 
{ 
    return _viewMatrix; 
}

const scmath::Mat4& Camera::getViewProjMatrix() const 
{ 
    return _viewProjMatrix; 
}

void Camera::recalculateViewMatrix()
{
    scmath::Mat4 transform = scmath::Mat4::translate(_position) * scmath::Mat4::rotate(scmath::degToRad(_rotation), scmath::Vec3(0, 0, 1));
    _viewMatrix = scmath::Mat4::inverse(transform);
    _viewProjMatrix = _projMatrix * _viewMatrix;
}
}