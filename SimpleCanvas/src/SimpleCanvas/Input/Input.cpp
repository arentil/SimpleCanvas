#include "Input.h"

namespace sc
{
bool Input::isKeyPressed(int code)
{  
    int state = glfwGetKey(glfwGetCurrentContext(), code);
    return (state == State::PRESSED || state == State::HOLD);
}

bool Input::isMousePressed(int code)
{  
    int state = glfwGetMouseButton(glfwGetCurrentContext(), code);
    return (state == State::PRESSED || state == State::HOLD);
}

std::pair<float, float> Input::getMousePos()
{
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    return std::make_pair((float)x, (float)y);
}

std::string Input::getKeyName(int code)
{
    const char * keyName = glfwGetKeyName(code, 0);
    if (keyName == nullptr)
        return "GLFW_KEY_UNKNOWN";
    return keyName;
}
} // namespace sc