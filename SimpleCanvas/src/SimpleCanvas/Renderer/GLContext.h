#pragma once

struct GLFWwindow;

namespace sc
{
class GLContext
{
public:
    explicit GLContext(GLFWwindow* glfwWindow);

    void init();
    void swapBuffers();

private:
    GLFWwindow* window;
};
} // namespace sc