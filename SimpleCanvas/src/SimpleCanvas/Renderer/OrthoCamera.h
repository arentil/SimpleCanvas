#pragma once

#include <SCMath.h>

namespace sc
{
class OrthoCamera
{
public:
    OrthoCamera(float left, float right, float bottom, float top);

    void setPosition(scmath::Vec3 const& position) { _position = position; recalculateViewMatrix(); }
    void setRotation(float rotation) { _rotation = rotation; recalculateViewMatrix(); }

    scmath::Vec3 getPosition() const { return _position; }
    float getRotation() const { return _rotation; }

    const scmath::Mat4& getProjMatrix() const { return _projMatrix; }
    const scmath::Mat4& getViewMatrix() const { return _viewMatrix; }
    const scmath::Mat4& getViewProjMatrix() const { return _viewProjMatrix; }

private:
    void recalculateViewMatrix();


    scmath::Mat4 _projMatrix;
    scmath::Mat4 _viewMatrix;
    scmath::Mat4 _viewProjMatrix;

    scmath::Vec3 _position;
    float _rotation = 0.0f;
};
} // namespace sc