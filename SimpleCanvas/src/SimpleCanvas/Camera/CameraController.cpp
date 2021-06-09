#include "CameraController.h"

#include "Renderer/Renderer.h"
#include "ObjectLogic/ObjectTree/SCObject.h"

namespace sc
{
CameraController::CameraController(CameraSettings const& settings)
: camera(settings, yaw, pitch)
{
    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
}

void CameraController::attachObject(SCObject *obj) 
{
    object = obj;
}

void CameraController::update(float deltaTime)
{
    float shiftMultiplier = 1.0f;
    if (Input::isKeyPressed(KEY_LEFT_SHIFT))
        shiftMultiplier = 6.0f;

    float velocity = movementSpeed * shiftMultiplier * deltaTime;

    scmath::Vec3 &objectPos = object->Transform.Translation;
    if (Input::isKeyPressed(KEY_W))
    {
        objectPos += camera.front * velocity;
    }
    if (Input::isKeyPressed(KEY_S))
    {
        objectPos -= camera.front * velocity;
    }
    if (Input::isKeyPressed(KEY_A))
    {
        objectPos -= camera.right * velocity;
    }
    if (Input::isKeyPressed(KEY_D))
    {
        objectPos += camera.right * velocity;
    }
    if (Input::isKeyPressed(KEY_E))
    {
        objectPos += camera.up * velocity;
    }
    if (Input::isKeyPressed(KEY_Q))
    {
        objectPos -= camera.up * velocity;
    }

    if (Input::isKeyPressed(KEY_ESC))
    {
        Renderer::setCursorMode(CursorMode::CURSOR_NORMAL);
        cursorMode = CursorMode::CURSOR_NORMAL;
        isFirstMouseEnter = true;
    }

    camera.setPosition(objectPos);
    camera.updateCameraVectors();
}

scmath::Vec3 CameraController::getPosition() const
{
    return object->Transform.Translation;
}

scmath::Mat4 CameraController::getViewProj() const
{
    return camera.getViewProj();
}

bool CameraController::isAABBvisible(AABB const& aabb) const
{
    return camera.isAABBvisible(aabb);
}

void CameraController::onEvent(Event &event) 
{
    EventDispatcher dispatcher;
    dispatcher.subscribe(this, &CameraController::onMouseMoved);
    dispatcher.subscribe(this, &CameraController::onMouseScrolled);
    dispatcher.subscribe(this, &CameraController::onMouseButtonPressed);
    dispatcher.subscribe(this, &CameraController::onWindowResize);
	dispatcher.dispatch(event);
}

void CameraController::onMouseMoved(MouseMovedEvent &event) 
{
    if (cursorMode == CursorMode::CURSOR_NORMAL)
        return;

    float xpos = event.getX();
    float ypos = event.getY();

    if (isFirstMouseEnter)
    {
        mouseLastX = xpos;
        mouseLastY = ypos;
        isFirstMouseEnter = false;
    }

    float xoffset = xpos - mouseLastX;
    float yoffset = mouseLastY - ypos;

    mouseLastX = xpos;
    mouseLastY = ypos;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    camera.setYawPitch(yaw, pitch);
    camera.updateCameraVectors();
}

void CameraController::onMouseScrolled(MouseScrollEvent &event) 
{
    camera.setZoom(event.GetYOffset());
}

void CameraController::onMouseButtonPressed(MouseButtonPressedEvent &event) 
{
    if (cursorMode != CursorMode::CURSOR_NORMAL)
        return;

    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
    cursorMode = CursorMode::CURSOR_DISABLED;
}

void CameraController::onWindowResize(WindowResizeEvent &event) 
{
    float width = (float)(event.getWidth());
    float height = (float)(event.getHeight());
    camera.setAspectSize(width, height);
}
} // namespace