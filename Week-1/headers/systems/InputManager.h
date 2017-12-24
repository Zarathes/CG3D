#pragma once
#ifndef __INPUTMANAGER_H_ 

// Structs
typedef struct GLFWwindow GLFWwindow;

// Additional includes
#ifndef __glew_h__
	#include <glew.h> // OpenGL
#endif __glew_h__

#include <vector>

namespace cg3d {
	class InputManager
	{
	public:

		InputManager();
		~InputManager();

		void ProcessInput();
		void CharacterCallback(GLFWwindow* window, GLuint codepoint);
	private:
		
		GLFWwindow *_window;
		std::vector<GLuint> _rawInput;
	};
}

#endif // !__INPUTMANAGER_H_ 