#include "CameraController.h"

#include "Renderer/PerspectiveCamera.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"

namespace sc
{
CameraController::CameraController(float aspectX, float aspectY)
: _aspectX(aspectX)
, _aspectY(aspectY)
, _camera(new PerspectiveCamera(70.0f, _aspectX / _aspectY, 0.01f, 1000.0f))
//, lastX(1280 / 2.0f)
//, _lastY(720 / 2.0f)
//, _camera(new OrthographicCamera(-_aspectX, _aspectX, -_aspectY,_aspectY, -1.0f, 1.0f)) // _camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
    _currentCursorMode = CursorMode::CURSOR_DISABLED;
    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
}

CameraPtr CameraController::getCamera() const
{
    return _camera;
}

void CameraController::onUpdate(float deltaTime)
{
    // forward and backward
    scmath::Vec3 cameraPos = _camera->getPosition();
    scmath::Vec3 cameraFront = _camera->getFrontVector();
    scmath::Vec3 cameraUp = _camera->getUpVector();
    

    float shiftMultiplier = 1.0f;
    if (Input::isKeyPressed(KEY_LEFT_SHIFT))
        shiftMultiplier = 6.0f;

    if (Input::isKeyPressed(KEY_W))
    {
        cameraPos += cameraFront * deltaTime * shiftMultiplier;
        _camera->setPosition(cameraPos);
    }
    if (Input::isKeyPressed(KEY_S))
    {
        cameraPos -= cameraFront * deltaTime * shiftMultiplier;
        _camera->setPosition(cameraPos);
    }
    if (Input::isKeyPressed(KEY_A))
    {
        cameraPos -= scmath::Vec3::normalized(scmath::Vec3::cross(cameraFront, scmath::Vec3(0, 1, 0))) * deltaTime * shiftMultiplier;
        _camera->setPosition(cameraPos);
    }
    if (Input::isKeyPressed(KEY_D))
    {
        cameraPos += scmath::Vec3::normalized(scmath::Vec3::cross(cameraFront, scmath::Vec3(0, 1, 0))) * deltaTime * shiftMultiplier;
        _camera->setPosition(cameraPos);
    }
    if (Input::isKeyPressed(KEY_E))
    {
        cameraPos += cameraUp * deltaTime * shiftMultiplier;
        _camera->setPosition(cameraPos);
    }
    if (Input::isKeyPressed(KEY_Q))
    {
        cameraPos -= cameraUp * deltaTime * shiftMultiplier;
        _camera->setPosition(cameraPos);
    }

    if (Input::isKeyPressed(KEY_ESC))
    {
        Renderer::setCursorMode(CursorMode::CURSOR_NORMAL);
        _currentCursorMode = CursorMode::CURSOR_NORMAL;
    }
}

void CameraController::onEvent(Event &event)
{
	EventDispatcher dispatcher;
    dispatcher.subscribe(this, &CameraController::onMouseMoved);
    dispatcher.subscribe(this, &CameraController::onMouseButtonPressed);
    dispatcher.subscribe(this, &CameraController::onWindowResize);
	dispatcher.dispatch(event);
}

void CameraController::onMouseMoved(MouseMovedEvent &event)
{
    if (_currentCursorMode == CursorMode::CURSOR_NORMAL)
        return;

    float x = event.getX();
    float y = event.getY();

    if (_isFirstMouse)
    {
        _lastX = x;
        _lastY = y;
        _isFirstMouse = false;
    }

    float xoffset = x - _lastX;
    float yoffset = _lastY - y;
    _lastX = x;
    _lastY = y;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    _yaw += xoffset;
    _pitch += yoffset;

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    scmath::Vec3 direction;
    direction.x = cos(scmath::degToRad(_yaw)) * cos(scmath::degToRad(_pitch));
    direction.y = sin(scmath::degToRad(_pitch));
    direction.z = sin(scmath::degToRad(_yaw)) * cos(scmath::degToRad(_pitch));
    _camera->setFrontVector(scmath::Vec3::normalized(direction));
}

void CameraController::onMouseButtonPressed(MouseButtonPressedEvent &event)
{
    if (_currentCursorMode != CursorMode::CURSOR_NORMAL)
        return;

    Renderer::setCursorMode(CursorMode::CURSOR_DISABLED);
    _currentCursorMode = CursorMode::CURSOR_DISABLED;
}

void CameraController::onWindowResize(WindowResizeEvent &event)
{
    _aspectX = (float)event.getWidth();
    _aspectY = (float)event.getHeight();
    auto aspectRatio = _aspectX / _aspectY;
    if (_camera->getType() == CameraType::ORTHOGRAPHIC)
        ((OrthographicCamera*)(_camera.get()))->setProjection(-(_aspectX / _aspectY) * _zoom, _aspectX / _aspectY * _zoom, -_zoom, _zoom, -1.0f, 1.0f);
    else if (_camera->getType() == CameraType::PERSPECTIVE)
        ((PerspectiveCamera*)(_camera.get()))->setProjection(70.0f, aspectRatio, 0.01f, 1000.0f);
}
} // namespace sc