#pragma once

#include "Renderer/Camera.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

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
    void onMouseScrolled(MouseScrollEvent &event);
    void onWindowResize(WindowResizeEvent &event);

    float _zoom = 1.0f;
    float _aspectX, _aspectY;
    CameraPtr _camera;

    scmath::Vec3 _position;
    float _translationSpeed = 1.0f;
};
} // namespace sc