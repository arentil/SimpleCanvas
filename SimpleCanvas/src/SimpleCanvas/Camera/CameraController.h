#pragma once

#include "CameraSettings.h"
#include "FPSCamera.h"
#include "ObjectLogic/AABB.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace sc
{
class SCObject;

class CameraController
{
public:
    CameraController(CameraSettings const& settings);

    void attachObject(SCObject *obj);
    void update(float deltaTime);
    void setPosition(scmath::Vec3 const& position);
    scmath::Vec3 getPosition() const;
    scmath::Mat4 getViewProj() const;
    bool isAABBvisible(AABB const& aabb) const;

    void onEvent(Event &event);
    void onMouseMoved(MouseMovedEvent &event);
    void onMouseScrolled(MouseScrollEvent &event);
    void onMouseButtonPressed(MouseButtonPressedEvent &event);
    void onWindowResize(WindowResizeEvent &event);

    bool isFirstMouseEnter = true;
    float mouseLastX, mouseLastY;
    float mouseSensitivity = 0.1f;
    float yaw =  -90.0f;
    float pitch = 0.0f;
    float movementSpeed = 2.5f;
    CursorMode cursorMode;

    FPSCamera camera;
    // object that the camera is attached to
    SCObject *object;
};
} // namespace sc