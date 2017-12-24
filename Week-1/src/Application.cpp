#include "Application.h"

// Additional includes
#ifndef __glew_h__
	#include <glew.h>
#endif // !__glew_h__

#ifndef _glfw3_h_
	#include <GLFW\glfw3.h>
#endif // !_glfw3_h_

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#ifndef _IOSTEAM_ 
	#include <iostream>
#endif // _IOSTEAM_
#ifndef _ALGORITHM_
	#include <algorithm>
#endif // _ALGORITHM_

#ifndef __INPUTMANAGER_H_
	#include "systems/InputManager.h"
#endif // !__INPUTMANAGER_H_

#ifndef __SHADERPROGAM_H_ 
	#include "graphics/ShaderProgram.h"
#endif // _SHADERPROGRAM_H_

#ifndef __MESH_H_
	#include "graphics/Mesh.h"
#endif // __MESH_H_

#ifndef __UTILITIES_H_
	#include "Utilities.h"
#endif // __UTILITIES_H_

#include <assert.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

Application::Application()
{
	Initialize();
	GameLoop();
	Release();
}
Application::~Application()
{
}

void Application::Initialize() 
{
	/* Initialize the library */
	assert(glfwInit() != -1);

	/* Create a windowed mode window and its OpenGL context */

	//int count;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	//GLFWmonitor** monitors = glfwGetMonitors(&count);
	//GLFWmonitor* monitor = monitors[count-1];
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	_window = glfwCreateWindow(1920*2, 1080*2, "CG3D", NULL, NULL);
//	glfwSetKeyCallback(window, key_callback);

	glfwGetWindowSize(_window, &_screen_width, &_screen_height);
	_aspect = (float)_screen_width / (float)_screen_height;

	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	_inputManager = new cg3d::InputManager();
	//_inputManager->SetFocussedWindow(_window);
	_program = new cg3d::ShaderProgram("res/shaders/Basic.shader");
	_cube = new cg3d::Mesh(_program);
	cg3d::MeshData data = {
		glm::vec3(2.0f, 2.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 90.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		0.5f,
		_program
	};
	_cube2 = new cg3d::Mesh(data);

	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glDepthFunc(GL_LESS));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	GLCall(glViewport(0, 0, _screen_width, _screen_height));
	_proj = glm::perspective(glm::radians(60.f), _aspect, 0.1f, 100.f);
	_view = glm::lookAt(glm::vec3(1.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	GLCall(glClearColor(0.25f, 0.25f, 0.25f, 1.0f));
}
void Application::GameLoop()
{
		
	float t = 0.0f;
	float dt = 1.0f / 60.0f;
	_frames = 0;

	float currentTime = (float)glfwGetTime();
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_window))
	{
		_frames++;
		float newTime = (float)glfwGetTime();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

		// Process Input
		ProcessInput();

		while (frameTime > 0.0f)
		{
			float deltaTime = std::min(frameTime, dt);
			Update(deltaTime);
			frameTime -= deltaTime;
			t += deltaTime;
		}

		Draw();

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(_window));

		/* Poll for and process events */
		GLCall(glfwPollEvents());

		if (t >= 1.0f)
		{
			std::cout << "fps: " << _frames <<  " ms: " << 1000.0f / _frames <<  std::endl;
			t -= 1.0f;
			_frames = 0;
		}
	}

}
void Application::ProcessInput()
{
	_inputManager->ProcessInput();
}
void Application::Update(float dt)
{	
	_cube->Update(dt);
	_cube2->Update(dt);
}
void Application::Draw()
{
	/* Render here */
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	/*for (int i = 0; i < 4; i++)
	{
		int x = i / 2;
		int y = i % 2;
		glViewport((_screen_width*0.5) * x, (_screen_height*0.5) * y, _screen_width*0.5, _screen_height*0.5);*/
	//}

	_cube->Draw(_proj * _view);
	_cube2->Draw(_proj * _view);
}
void Application::Release()
{
	glfwTerminate();
}