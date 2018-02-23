#include "Window.h"

// Namespaces
using namespace cg3d;

// Additional includes
#ifndef INPUTMANAGER_H_
	#include "systems/InputManager.h"
#endif // !INPUTMANAGER_H_

#ifndef ENGINE_H_
	#include "Engine.h"
#endif // !ENGINE_H_

Window::Window(Engine* engine, int width, int height, const char* name, bool fullscreen)
	: _delegate(engine)
	, _screenWidth(width)
	, _screenHeight(height)
	, _aspect((float)_screenWidth / (float)_screenHeight)
	, _window(nullptr)
	, _rawInput(std::vector<KeyStroke>())
{
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
	_window = glfwCreateWindow(width, height, name, monitor, NULL);
	SetActiveWindow();
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}


#pragma warning(push)
#pragma warning(disable:4100)
void Window::OnResize(GLFWwindow* window, int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;
	_delegate->_renderer->ChangeFrustrum(width, height);
	std::cout << "Width: " << width << ", Height: " << height << std::endl;
}
void Window::CharacterCallback(GLFWwindow* window, KeyStroke stroke)
{
	std::cout << "Input: " << stroke._key << " " << ((stroke._action == KEY_PRESS) ? "Pressed" : (stroke._action == KEY_RELEASE) ? "Released" : "Repeat") << std::endl;
	_rawInput.push_back(stroke);
}
#pragma warning(pop)

void Window::SetActiveWindow()
{
	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, this);
	GLFWwindowsizefun resize_callback = [](GLFWwindow* window, int width, int height) -> void
	{
		auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));
		self.OnResize(window, width, height);
	};
	glfwSetWindowSizeCallback(_window, resize_callback);

	GLFWkeyfun key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
	{
		auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

		KeyStroke stroke{key, scancode, action, mods};
		self.CharacterCallback(window, stroke);
	};
	glfwSetKeyCallback(_window, key_callback);
}

std::vector<KeyStroke> Window::GetRawInput() {
	std::vector<KeyStroke> data = _rawInput;
	ClearInput();
	return data;
}

void Window::ClearInput()
{
	_rawInput.clear();
}