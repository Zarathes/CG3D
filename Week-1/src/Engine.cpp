#include "Engine.h"

// Namespaces
using namespace cg3d;

// Additional Includes
#ifndef __glew_h__
	#include <glew.h>
#endif // !__glew_h__

#ifndef _glfw3_h_
	#include <GLFW\glfw3.h>
#endif // !_glfw3_h_

#ifndef __WINDOW_H_
	#include  "Window.h"
#endif __WINDOW_H_

#ifndef __SCENEMANAGEGER_H_
	#include "systems/SceneManager.h"
#endif // !__SCENEMANAGEGER_H_

#ifndef __INPUTMANAGER_H_
	#include "systems/InputManager.h"
#endif // !__INPUTMANAGER_H_

#include "Utilities.h"

#include <assert.h>

// ----- Main -----
// Entry point of the application
// ----------------
int main()
{
	Engine* app = new Engine();
	app->GameLoop();
	delete app;
}

// ----- GameLoop -----
// Core of the engine
// This method is the beginning and end of
// the engine. It handles set up, shutdown and
// everything in between.
// --------------------
void Engine::GameLoop()
{
	Initialize();

	bool shouldQuit = false;
	while (!shouldQuit)
	{
		// poll Input
		_inputManager->ProcessInput();
		//_sceneManager->_currentScene->Update(0.0f);
		//_sceneManager->_currentScene->Redraw();

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(_window->_window));

		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}

	Finalize();
}

// ----- Initialize -----
// This method sets up all needed systems 
// and variables. 
// ----------------------
void Engine::Initialize()
{
	// Initialize glfw
	assert(glfwInit() != -1);

	// Init Memory
	// Init Timer
	_inputManager = new InputManager();
	_window = new Window(1920, 1080, "CG3D", false);
	_window->SetCurrentContext(_inputManager);

	_sceneManager = new SceneManager();
}

void Engine::Finalize()
{
	// fin Input
	// fin Scene
	// fin Window
	// fin Timer
	// fin Memory
	   
	// fin OpenGL/GLEW/GLFW
}