#include "CameraController.h"

#include "Renderer/Renderer.h"
#include "ObjectLogic/ObjectTree/SCObject.h"

namespace sc
{
CameraController::CameraController(CameraSettings const& settings)
: camera(settings, yaw, pitch)
{
    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
    dispatcher.subscribe(this, &CameraController::onMouseMoved);
    dispatcher.subscribe(this, &CameraController::onMouseScrolled);
    dispatcher.subscribe(this, &CameraController::onMouseButtonPressed);
    dispatcher.subscribe(this, &CameraController::onWindowResize);
}

void CameraController::attachObject(SCObject *obj) 
{
    object = obj;
}

void CameraController::update(float deltaTime)
{
    float speed = movementSpeed * deltaTime;
    if (Input::isKeyPressed(KEY_LEFT_SHIFT))
        speed *= shiftMultiplier;

    scmath::Vec3 const right = camera.right;
    scmath::Vec3 const front = right.cross(scmath::Vec3::Up() * -1);

    lastPosition = object->Transform.Translation;
    scmath::Vec3 &objectPos = object->Transform.Translation;
    if (Input::isKeyPressed(KEY_W))
    {
        objectPos += front * speed;
    }
    if (Input::isKeyPressed(KEY_S))
    {
        objectPos -= front * speed;
    }
    if (Input::isKeyPressed(KEY_D))
    {
        objectPos += right * speed;
    }
    if (Input::isKeyPressed(KEY_A))
    {
        objectPos -= right * speed;
    }
    if (Input::isKeyPressed(KEY_SPACE) && object->Rigidbody->IsGrounded)
    {
        object->Rigidbody->addForce(scmath::Vec3::Up() * jumpForceMultiplier);
    }

    if (!(object->Rigidbody->IsKinematic))
    {
        if (Input::isKeyPressed(KEY_E))
        {
            objectPos += scmath::Vec3::Up() * speed;
        }
        if (Input::isKeyPressed(KEY_Q))
        {
            objectPos += scmath::Vec3::Down() * speed;
        }
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

void CameraController::setPosition(scmath::Vec3 const& position) 
{
    camera.setPosition(position);
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