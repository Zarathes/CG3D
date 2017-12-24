#include "systems/InputManager.h"

using namespace cg3d;

// Additional includes
#ifndef _glfw3_h_
	#include <GLFW\glfw3.h>
#endif // !_glfw3_h_

#ifndef  _IOSTREAM_
	#include <iostream>
#endif // ! _IOSTREAM_

InputManager::InputManager()
{
	_rawInput = std::vector<GLuint>();
}
InputManager::~InputManager()
{
}

void InputManager::ProcessInput()
{
	if (!_rawInput.empty())
	{
		std::cout << "Key Input ";
		for (size_t i = 0; i < _rawInput.size(); i++)
		{	
			std::cout << (char)_rawInput.at(i);
		}
		std::cout << std::endl;

		_rawInput.clear();
	}
}

void InputManager::CharacterCallback(GLFWwindow* window, GLuint codepoint)
{
	_rawInput.push_back(codepoint);
}