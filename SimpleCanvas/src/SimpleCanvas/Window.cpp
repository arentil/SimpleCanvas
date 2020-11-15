#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace sc {
namespace {
static void GLFWErrorCallback(int error, const char* description)
{
	LOG_ERROR("GLFW ERROR CODE: " + std::to_string(error) + std::string(description));
}
}


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
		glfwSetErrorCallback(GLFWErrorCallback);
		GLFW_INITIALIZED = true;
	}

	window = glfwCreateWindow(glfwData.width, glfwData.height, glfwData.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &glfwData);	// assosiate wrapper pointer to the window
	setVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h)
	{
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);	// register callback
		data.width = w;
		data.height = h;

		WindowResizeEvent event(w, h);
		data.eventCallback(event);
	});

	glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.eventCallback(event);
	});

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.eventCallback(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);
		MouseScrollEvent event((float)xOffset, (float)yOffset);
		data.eventCallback(event);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);
		MouseMovedEvent event((float)xPos, (float)yPos);
		data.eventCallback(event);
	});
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
	glfwData.eventCallback = callback;
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