#pragma once

#include "Renderer/Camera.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#include <SCMath.h>


namespace sc
{
class CameraController
{
public:
    CameraController(float aspectX, float aspectY);

    CameraPtr getCamera() const;

    void onUpdate(float deltaTime);
    void onEvent(Event &event);

private:
    void onMouseMoved(MouseMovedEvent &event);
    void onMouseScrolled(MouseScrollEvent &event);
    void onMouseButtonPressed(MouseButtonPressedEvent &event);
    void onWindowResize(WindowResizeEvent &event);

    float _zoom = 1.0f;
    float _aspectX, _aspectY;
    CameraPtr _camera;

    float _translationSpeed = 1.0f;
    float _yaw = 0.0f;
    float _pitch = 0.0f;
    float _lastX, _lastY;
    bool _isFirstMouse = true;
    CursorMode _currentCursorMode;
};
} // namespace sc