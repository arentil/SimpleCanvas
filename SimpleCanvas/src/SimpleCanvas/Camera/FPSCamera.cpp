#include "FPSCamera.h"

#include "Renderer/Renderer.h"

namespace sc
{
FPSCamera::FPSCamera(CameraSettings const& camSettings, float pYaw, float pPitch)
: settings(camSettings)
, yaw(pYaw)
, pitch(pPitch)
, projectionMatrix(scmath::Mat4::perspective(settings.Fov, settings.getAspect() , settings.Near, settings.Far))
{
    frustum.setCamInternals(settings.Fov, settings.getAspect() , settings.Near, settings.Far);
    updateCameraVectors();
}

void FPSCamera::updateCameraVectors() 
{
    // recalculate front vector
    front.x = std::cos(scmath::degToRad(yaw)) * std::cos(scmath::degToRad(pitch));
    front.y = std::sin(scmath::degToRad(pitch));
    front.z = std::sin(scmath::degToRad(yaw)) * std::cos(scmath::degToRad(pitch));
    front = front.normalized();

    // recalculate right and up vector
    right = front.cross(worldUp).normalized();
    up = right.cross(front).normalized();

    frustum.setCamDef(position, position + front, up);
}

void FPSCamera::setPosition(scmath::Vec3 const& pPosition) 
{
    position = pPosition;
}

void FPSCamera::setYawPitch(float pYaw, float pPitch) 
{
    yaw = pYaw;
    pitch = pPitch;
}

void FPSCamera::setZoom(float yOffset) 
{
    float offset = settings.Fov - (yOffset * 2);
    settings.Fov = std::clamp(offset, settings.zoomMin, settings.zoomMax);    
    projectionMatrix = scmath::Mat4::perspective(settings.Fov, settings.getAspect(), settings.Near, settings.Far);
    updateCameraVectors();
    frustum.setCamInternals(settings.Fov, settings.getAspect(), settings.Near, settings.Far);
}

void FPSCamera::setAspectSize(float width, float height) 
{
    settings.AspectWidth = width;
    settings.AspectHeight = height;
    projectionMatrix = scmath::Mat4::perspective(settings.Fov, settings.getAspect(), settings.Near, settings.Far);
    frustum.setCamInternals(settings.Fov, settings.getAspect(), settings.Near, settings.Far);
}

scmath::Mat4 FPSCamera::getViewProj() const
{
    return projectionMatrix * scmath::Mat4::lookAt(position,  position + front, up);
}

bool FPSCamera::isAABBvisible(AABB const& aabb) const
{
    return frustum.isAABBvisible(aabb);
}
} // namespace sc