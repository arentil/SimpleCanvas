#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Utils/StringUtils.h"

namespace sc
{
namespace
{
std::pair<int, int> getGlVersion()
{
	std::string glVersion((char*)glGetString(GL_VERSION));
	auto splitted = splitString(glVersion, ' ');
	auto versionStr = splitString(splitted.front(), '.');
	const int glVersionMajor = std::stoi(versionStr.front());
	const int glVersionMinor = std::stoi(*std::next(versionStr.begin()));
	return std::make_pair(glVersionMajor, glVersionMinor);
}
} // namespace

GLContext::GLContext(GLFWwindow* glfwWindow)
: window(glfwWindow)
{}

void GLContext::init()
{
	glfwMakeContextCurrent(window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);	// exactly like in the glfw context guide
	SC_ASSERT(status, "Assertion failed! Failed to initialize glad!");
	LOG_INFO("%s, %s, %s", glGetString(GL_VENDOR) ,glGetString(GL_RENDERER), glGetString(GL_VERSION));

	if 	(auto [versionMajor, versionMinor] = getGlVersion(); versionMajor < 4 || versionMinor < 5)
	{
		LOG_ERROR("OPENGL %d.%d NOT SUPPORTED! PLEASE INSTALL OPENGL 4.5 OR LATER", versionMajor, versionMinor);
		exit(1);
	}
}

void GLContext::swapBuffers()
{
    glfwSwapBuffers(window);
}
} // namespace sc