#pragma once

#include <SCMath.h>

#include "Frustum.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace sc
{
// defaults
constexpr float YAW         = -90.0f;
constexpr float PITCH       =  0.0f;
constexpr float SPEED       =  2.5f;
constexpr float SENSITIVITY =  0.1f;
constexpr float FOV        =  70.0f;

class FPSCamera
{
public:
    FPSCamera(scmath::Vec3 const& position = scmath::Vec3(0.0f, 0.0f, 0.0f),
              scmath::Vec3 const& worldUp = scmath::Vec3(0.0f, 1.0f, 0.0f),
              float yaw = YAW,
              float pitch = PITCH);

    void updateCameraVectors();
    scmath::Mat4 getViewProjMatrix() const;
    scmath::Vec3 getPosition() const;

    void update(float deltaTime);
    void onEvent(Event &event);

    void onMouseMoved(MouseMovedEvent &event);
    void onMouseScrolled(MouseScrollEvent &event);
    void onMouseButtonPressed(MouseButtonPressedEvent &event);
    void onWindowResize(WindowResizeEvent &event);

    scmath::Vec3 _position;
    scmath::Vec3 _front;
    scmath::Vec3 _up;
    scmath::Vec3 _right;
    scmath::Vec3 _worldUp;  // !!!

    // euler angles
    float _yaw, _pitch;

    //camera options
    float _movementSpeed;
    float _mouseSensitivity;
    float _fov;

    scmath::Mat4 _projectionMatrix;
    scmath::Mat4 _viewMatrix;
    scmath::Mat4 _viewProjMatrix;

    bool firstMouse = true;
    float lastX, lastY;

    CursorMode _currentCursorMode;

    Frustum _frustum;
};
} // namespace sc