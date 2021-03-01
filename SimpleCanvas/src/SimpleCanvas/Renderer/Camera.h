#pragma once

#include <memory>

#include <SCMath.h>

namespace sc
{
enum class CameraType
{
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Camera;
using CameraPtr = std::shared_ptr<Camera>;

class Camera
{
public:
    Camera(CameraType type, scmath::Mat4 const& projectionMatrix, scmath::Mat4 const& viewMatrix);
    virtual ~Camera() = default;

    CameraType getType() const;

    void setPosition(scmath::Vec3 const& position);
    scmath::Vec3 getPosition() const;

    void setRotation(float rotation);
    float getRotation() const;

    const scmath::Mat4& getProjMatrix() const;
    const scmath::Mat4& getViewMatrix() const;
    const scmath::Mat4& getViewProjMatrix() const;

protected:
    void recalculateViewMatrix();

    const CameraType _type;

    scmath::Mat4 _projMatrix;
    scmath::Mat4 _viewMatrix;
    scmath::Mat4 _viewProjMatrix;

    scmath::Vec3 _position;
    float _rotation = 0.0f;
};
} // namespace sc