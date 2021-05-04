#include "FPSCamera.h"

#include "Renderer/Renderer.h"

namespace sc
{
FPSCamera::FPSCamera(scmath::Vec3 const& position, scmath::Vec3 const& worldUp, float yaw, float pitch)
: _position(position)
, _worldUp(worldUp)
, _yaw(yaw)
, _pitch(pitch)
, _movementSpeed(SPEED)
, _mouseSensitivity(SENSITIVITY)
, _zoom(ZOOM)
, _projectionMatrix(scmath::Mat4::perspective(70.0f, 1280.0f/720.0f , 0.01f, 100.0f))
{
    updateCameraVectors();
    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
}

void FPSCamera::updateCameraVectors() 
{
    // calculate new front
    scmath::Vec3 front;
    front.x = std::cos(scmath::degToRad(_yaw)) * std::cos(scmath::degToRad(_pitch));
    front.y = std::sin(scmath::degToRad(_pitch));
    front.z = std::sin(scmath::degToRad(_yaw)) * std::cos(scmath::degToRad(_pitch));
    _front = front.normalized();

    // recalculate right and up vector
    _right = _front.cross(_worldUp).normalized();
    _up = _right.cross(_front).normalized();
}

scmath::Mat4 FPSCamera::getViewProjMatrix() const
{
    return _projectionMatrix * scmath::Mat4::lookAt(_position,  _position + _front, _up);
}

scmath::Vec3 FPSCamera::getPosition() const
{
    return _position;
}

void FPSCamera::update(float deltaTime) 
{
    float shiftMultiplier = 1.0f;
    if (Input::isKeyPressed(KEY_LEFT_SHIFT))
        shiftMultiplier = 6.0f;

    float velocity = _movementSpeed * shiftMultiplier * deltaTime;

    if (Input::isKeyPressed(KEY_W))
    {
        _position += _front * velocity;
    }
    if (Input::isKeyPressed(KEY_S))
    {
        _position -= _front * velocity;
    }
    if (Input::isKeyPressed(KEY_A))
    {
        _position -= _right * velocity;
    }
    if (Input::isKeyPressed(KEY_D))
    {
        _position += _right * velocity;
    }
    if (Input::isKeyPressed(KEY_E))
    {
        _position += _up * velocity;
    }
    if (Input::isKeyPressed(KEY_Q))
    {
        _position -= _up * velocity;
    }

    if (Input::isKeyPressed(KEY_ESC))
    {
        Renderer::setCursorMode(CursorMode::CURSOR_NORMAL);
        _currentCursorMode = CursorMode::CURSOR_NORMAL;
    }
}

void FPSCamera::onEvent(Event &event) 
{
	EventDispatcher dispatcher;
    dispatcher.subscribe(this, &FPSCamera::onMouseMoved);
    dispatcher.subscribe(this, &FPSCamera::onMouseButtonPressed);
    dispatcher.subscribe(this, &FPSCamera::onWindowResize);
    dispatcher.subscribe(this, &FPSCamera::onMouseScrolled);
	dispatcher.dispatch(event);
}

void FPSCamera::onMouseMoved(MouseMovedEvent &event) 
{
    if (_currentCursorMode == CursorMode::CURSOR_NORMAL)
        return;

    float xpos = event.getX();
    float ypos = event.getY();

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void FPSCamera::onMouseScrolled(MouseScrollEvent &event) 
{
    float offset = _zoom - (event.GetYOffset() * 2);
    _zoom = std::clamp(offset, 20.0f, 120.0f);    
    _projectionMatrix = scmath::Mat4::perspective(_zoom, 1280.0f/720.0f , 0.01f, 100.0f);
}

void FPSCamera::onMouseButtonPressed(MouseButtonPressedEvent &event) 
{    
    if (_currentCursorMode != CursorMode::CURSOR_NORMAL)
        return;

    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
    _currentCursorMode = CursorMode::CURSOR_DISABLED;
}

void FPSCamera::onWindowResize(WindowResizeEvent &event) 
{
    auto aspectRatio = (float)event.getWidth() / (float)event.getHeight();
    _projectionMatrix = scmath::Mat4::perspective(_zoom, aspectRatio , 0.01f, 100.0f);
}
} // namespace sc