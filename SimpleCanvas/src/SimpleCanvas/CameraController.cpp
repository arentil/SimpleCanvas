#include "CameraController.h"

#include "Renderer/PerspectiveCamera.h"
#include "Renderer/OrthographicCamera.h"
#include "Input/Input.h"

namespace sc
{
CameraController::CameraController(float aspectX, float aspectY)
: _aspectX(aspectX)
, _aspectY(aspectY)
// , _camera(new PerspectiveCamera(70.0f, _aspectX / _aspectY, 0.0001f, 10.0f))
, _camera(new OrthographicCamera(-_aspectX, _aspectX, -_aspectY,_aspectY, -1.0f, 1.0f)) // _camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
}

CameraPtr CameraController::getCamera() const
{
    return _camera;
}

void CameraController::onUpdate(float deltaTime)
{
    // forward and backward
    if (Input::isKeyPressed(KEY_UP))
    {
        _position.z -= _translationSpeed * deltaTime;
    }
    if (Input::isKeyPressed(KEY_DOWN))
    {
        _position.z += _translationSpeed * deltaTime;
    }

    // up and down
    if (Input::isKeyPressed(KEY_W))
    {
        _position.y += _translationSpeed * deltaTime;
    }
    if (Input::isKeyPressed(KEY_S))
    {
        _position.y -= _translationSpeed * deltaTime;
    }

    // left and right
    if (Input::isKeyPressed(KEY_A))
    {
        _position.x -= _translationSpeed * deltaTime;
    }

    if (Input::isKeyPressed(KEY_D))
    {
        _position.x += _translationSpeed * deltaTime;
    }

    _camera->setPosition(_position);
}

void CameraController::onEvent(Event &event)
{
	EventDispatcher dispatcher;
	dispatcher.subscribe(this, &CameraController::onMouseScrolled);
    dispatcher.subscribe(this, &CameraController::onWindowResize);
	dispatcher.dispatch(event);
}

void CameraController::onMouseScrolled(MouseScrollEvent &event)
{
    ////_position.z  // divide by 5 to slow down zomming
    //_zoom -= (event.GetYOffset() / 5);
    if (_camera->getType() == CameraType::ORTHOGRAPHIC)
        ((OrthographicCamera*)(_camera.get()))->setProjection(-(_aspectX / _aspectY) * _zoom, _aspectX / _aspectY * _zoom, -_zoom, _zoom, -1.0f, 1.0f);
}

void CameraController::onWindowResize(WindowResizeEvent &event)
{
    _aspectX = (float)event.getWidth();
    _aspectY = (float)event.getHeight();
    auto aspectRatio = _aspectX / _aspectY;
    if (_camera->getType() == CameraType::ORTHOGRAPHIC)
        ((OrthographicCamera*)(_camera.get()))->setProjection(-(_aspectX / _aspectY) * _zoom, _aspectX / _aspectY * _zoom, -_zoom, _zoom, -1.0f, 1.0f);
    else if (_camera->getType() == CameraType::PERSPECTIVE)
        ((PerspectiveCamera*)(_camera.get()))->setProjection(70.0f, aspectRatio, 0.0001f, 10.0f);
}
} // namespace sc