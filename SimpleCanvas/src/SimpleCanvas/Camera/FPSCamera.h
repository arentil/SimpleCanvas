#pragma once

#include <SCMath.h>

#include "Frustum.h"
#include "ObjectLogic/AABB.h"
#include "CameraSettings.h"

namespace sc
{
class FPSCamera
{
public:
    FPSCamera(CameraSettings const& camSettings, float pYaw, float pPitch);

    void updateCameraVectors();
    void setPosition(scmath::Vec3 const& pPosition);
    void setYawPitch(float pYaw, float pPitch);
    void setZoom(float yOffset);
    void setAspectSize(float width, float height);

    scmath::Mat4 getViewProj() const;
    bool isAABBvisible(AABB const& aabb) const;

    // saving position, yaw and pitch as reference
    // so we do not need to call update fields functions all the time
    scmath::Vec3 position;
    float yaw;
    float pitch;

    scmath::Vec3 front;
    scmath::Vec3 up;
    scmath::Vec3 right;
    scmath::Vec3 worldUp = {0.0f, 1.0f, 0.0f};      // static world up vector, different than up that is relative to the camera rotation etc...

    CameraSettings settings;

private:
    scmath::Mat4 projectionMatrix;
    Frustum frustum;
};
} // namespace sc