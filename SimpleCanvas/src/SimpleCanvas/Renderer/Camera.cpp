#include "Camera.h"

namespace sc
{
Camera::Camera(CameraType type, scmath::Mat4 const& projectionMatrix, scmath::Mat4 const& viewMatrix)
: _type(type)
, _projMatrix(projectionMatrix)
, _viewMatrix(viewMatrix)
, _position(0.0f, 0.0f, 3.0f)
, _front(0.0f, 0.0f, -1.0f)
, _up(0.0f, 1.0f, 0.0f)
{
    //_viewProjMatrix = _projMatrix * _viewMatrix;
    recalculateViewMatrix();
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

void Camera::setFrontVector(scmath::Vec3 const& front)
{
    _front = front;
    recalculateViewMatrix();
}

const scmath::Vec3& Camera::getFrontVector() const 
{ 
    return _front; 
}

const scmath::Vec3& Camera::getUpVector() const
{
    return _up;
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
   // scmath::Mat4 transform = scmath::Mat4::translate(_position);
    //_viewMatrix = scmath::Mat4::inverse(transform);
    _viewMatrix = scmath::Mat4::lookAt(_position,  _position + _front, _up);
    _viewProjMatrix = _projMatrix * _viewMatrix;
}
}