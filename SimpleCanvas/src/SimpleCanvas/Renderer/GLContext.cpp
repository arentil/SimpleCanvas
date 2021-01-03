#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace sc
{
GLContext::GLContext(GLFWwindow* glfwWindow)
: window(glfwWindow)
{}

void GLContext::init()
{
	glfwMakeContextCurrent(window);
	// add and init glad
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);	// exactly like in the glfw context guide
	SC_ASSERT(status, "Assertion failed! Failed to initialize glad!");
	LOG_INFO("%s, %s, %s", glGetString(GL_VENDOR) ,glGetString(GL_RENDERER), glGetString(GL_VERSION));
}

void GLContext::swapBuffers()
{
    glfwSwapBuffers(window);
}
} // namespace sc