#pragma once
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

// Defines
#define MAXSAMPLES 100

// Structs
typedef struct GLFWwindow GLFWwindow;

// Additional includes
#include <glm.hpp>

namespace cg3d {
	class InputManager;
	class ShaderProgram;
	class Mesh;
}

class Application
{
public:
						Application();
						~Application();
private:
	void				Initialize();
	void				GameLoop();
	void				ProcessInput();
	void				Update(float delta);
	void				Draw();
	void				Release();

	GLFWwindow*			_window;

	int					_frames;
	int					_screen_width;
	int					_screen_height;
	float				_aspect;

	glm::mat4			_proj;
	glm::mat4			_view;

	cg3d::InputManager	*_inputManager;
	cg3d::ShaderProgram *_program;
	cg3d::Mesh	        *_cube;
	cg3d::Mesh	        *_cube2;
};
#endif // !__APPLICATION_H_
