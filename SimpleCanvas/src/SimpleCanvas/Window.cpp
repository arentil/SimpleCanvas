#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Input/Input.h"
#include "Renderer/GLContext.h"

namespace sc 
{
namespace 
{
static void GLFWErrorCallback(int error, const char* description)
{
	LOG_ERROR("GLFW ERROR CODE: %d, %s", error, description);
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
		SC_ASSERT(success, "Assertion failed! Failed to initialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		GLFW_INITIALIZED = true;
	}

	// create GLFW window
	glfwWindow = glfwCreateWindow(glfwData.width, glfwData.height, glfwData.title.c_str(), nullptr, nullptr);

	glContext = new GLContext(glfwWindow);
	glContext->init();

	glfwSetWindowUserPointer(glfwWindow, &glfwData);	// assosiate wrapper pointer to the window
	setVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow *window, int w, int h)
	{
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);	// register callback
		data.width = w;
		data.height = h;

		WindowResizeEvent event(w, h);
		data.eventCallback(event);
	});

	glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow *window) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.eventCallback(event);
	});

	glfwSetKeyCallback(glfwWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case State::PRESSED:
			{
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case State::HOLD:
			{
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
			case State::RELEASE:
			{
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods) {
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

	glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);
		MouseScrollEvent event((float)xOffset, (float)yOffset);
		data.eventCallback(event);
	});

	glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xPos, double yPos) {
		GLFWWindowData& data = *(GLFWWindowData*)glfwGetWindowUserPointer(window);
		MouseMovedEvent event((float)xPos, (float)yPos);
		data.eventCallback(event);
	});
}

void Window::shutdown()
{
	glfwDestroyWindow(glfwWindow);
}

void Window::update()
{
	glfwPollEvents();		// obvious
	glContext->swapBuffers();
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