#include "Window.h"

namespace sc {

Window::Window(WindowProperties const& properties)
{
	init(properties);
}

Window::~Window()
{
	shutdown();
}

void Window::init(WindowProperties const& properties)
{
	glfwData.title = properties.title;
	glfwData.width = properties.width;
	glfwData.height = properties.height;

	LOG_INFO("Generating OpenGl window!");

	if (!GLFW_INITIALIZED)
	{
		int success = glfwInit();
		SC_ASSERT(success, "Failed to initialize GLFW!");

		GLFW_INITIALIZED = true;
	}

	window = glfwCreateWindow(glfwData.width, glfwData.height, glfwData.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &glfwData);
	setVSync(true);
}

void Window::shutdown()
{
	glfwDestroyWindow(window);
}

void Window::onUpdate()
{
	glfwPollEvents();		// obvious
	glfwSwapBuffers(window); // obvious
}

uint32_t Window::getWidth() const
{
	return glfwData.width;
}

uint32_t Window::getHeight() const
{
	return glfwData.height;
}

void Window::setEventCallback(EventCallbackFn const& callback)
{

}

void Window::setVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	glfwData.VSync = enabled;
}


bool Window::isVSync() const
{
	return glfwData.VSync;
}

Window* Window::create(WindowProperties const& properties)
{
	return new Window(properties);
}

} // namespace sc