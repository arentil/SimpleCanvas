#pragma once

#include "Core.h"
#include "Events/Event.h"

#include <GLFW/glfw3.h>

namespace sc {
class GLContext;
static bool GLFW_INITIALIZED = false;

class Window;
using WindowPtr = std::unique_ptr<Window>;


class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowProperties
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProperties(std::string const& pTitle = "Simple Canvas Window", uint32_t pWidth = 1280u, uint32_t pHeight = 720u)
			: title(pTitle), width(pWidth), height(pHeight) {}
	};

	Window(WindowProperties const& properties);
	~Window();

	void update();
	uint32_t getWidth() const;
	uint32_t getHeight() const;

	void setEventCallback(EventCallbackFn const& callback);
	void setVSync(bool enabled);
	bool isVSync() const;

	static Window* create(WindowProperties const& properties = WindowProperties());

private:
	void init(WindowProperties const& properties);
	void shutdown();

	GLFWwindow *glfwWindow;
	GLContext *glContext;

	struct GLFWWindowData
	{
		std::string title;
		uint32_t width, height;
		bool VSync;

		EventCallbackFn eventCallback;
	};

	GLFWWindowData glfwData;
};
} // namespace sc