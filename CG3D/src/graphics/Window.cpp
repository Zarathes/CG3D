#include "graphics/Window.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "systems/input/InputManager.h"
#include "systems/input/Mouse.h"
#include "data/Events.h"

#include "graphics/Scene.h"

Window::Window(int width, int height, const char* name, bool fullscreen)
	: _windowHandle(nullptr)
{
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
	_windowHandle = glfwCreateWindow(width, height, name, monitor, NULL);
	glfwMakeContextCurrent(_windowHandle);
	
	glfwSetWindowUserPointer(_windowHandle, this);
	GLFWwindowsizefun resize_callback = [](GLFWwindow* window, int width, int height) -> void
	{
		auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));
		self.notify(EventWindowResize({ width, height }));
	};
	glfwSetWindowSizeCallback(_windowHandle, resize_callback);

	GLFWkeyfun key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
	{
		InputManager::get().onKeyInput({ key, scancode, action, mods });
	};
	glfwSetKeyCallback(_windowHandle, key_callback);

	GLFWcursorposfun cursor_callback = [](GLFWwindow* window, double x, double y) -> void
	{
		InputManager::get().onMouseMovement({x, y});
	};
	glfwSetCursorPosCallback(_windowHandle, cursor_callback);

	GLFWmousebuttonfun mouse_callback = [](GLFWwindow* window, int button, int action, int mod) -> void
	{
		InputManager::get().onMouseClick({button, action, mod});
	};
	glfwSetMouseButtonCallback(_windowHandle, mouse_callback);

	GLFWscrollfun scroll_callback = [](GLFWwindow* window, double xOffset, double yOffset) -> void
	{
		InputManager::get().onMouseScroll({ xOffset, yOffset});
	};
	glfwSetScrollCallback(_windowHandle, scroll_callback);
}

Window::~Window()
{
	glfwDestroyWindow(_windowHandle);
}

void Window::start()
{
	int width, height;
	glfwGetWindowSize(_windowHandle, &width, &height);
	notify(EventWindowResize({ width, height }));
}

GLFWwindow * Window::getWindowHandle() const
{
	return _windowHandle;
}