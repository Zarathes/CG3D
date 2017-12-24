#include "Window.h"

// Namespaces
using namespace cg3d;

// Additional includes
#ifndef __glew_h__
#include <glew.h>
#endif // !__glew_h__

#ifndef _glfw3_h_
	#include <GLFW\glfw3.h>
#endif // !_glfw3_h_

#ifndef __INPUTMANAGER_H_
	#include "systems/InputManager.h"
#endif // !__INPUTMANAGER_H_

#include <iostream>

void Window::OnResize(GLFWwindow* window, int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;
	_aspect = (float)_screenWidth / (float)_screenHeight;

	std::cout << "Width: " << width << ", Height: " << height << std::endl;
}

void Window::SetCurrentContext(InputManager* manager)
{
	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, this);
	GLFWwindowsizefun resize_callback = [](GLFWwindow* window, int width, int height) -> void
	{
		auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));
		self.OnResize(window, width, height);
	};
	glfwSetWindowSizeCallback(_window, resize_callback);
	
	glfwSetWindowUserPointer(_window, manager);
	GLFWcharfun key_callback = [](GLFWwindow* window, GLuint codepoint) -> void
	{
		auto& self = *static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		self.CharacterCallback(window, codepoint);
	};
	glfwSetCharCallback(_window, key_callback);
}

Window::Window(int width, int height, char* name, bool fullscreen)
	: _screenWidth(width)
	, _screenHeight(height)
	, _aspect((float)_screenWidth / (float)_screenHeight)
	, _window(nullptr)
{
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
	_window = glfwCreateWindow(width, height, name, monitor, NULL);	
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}