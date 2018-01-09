#include "Engine.h"

// Namespaces
using namespace cg3d;

// Additional Includes
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

Engine::Engine()
	: _shouldClose(false)
{
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
	while (!_shouldClose)
	{
		_sceneManager->_currentScene->ProcessInput(_inputManager->ProcessRawInput(_window->GetRawInput()));
		_sceneManager->_currentScene->Update(0.0f);
		_sceneManager->_currentScene->Redraw();

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
	if (glfwInit() != GLFW_TRUE)
		std::cout << "Error: failed to intitialize glfw" << std::endl;
	
	_window = new Window(1920, 1080, "CG3D", false);
	_window->SetCurrentContext();

	if (GLint GlewInitResult = glewInit() != GLEW_OK)
		std::cout << "Error: " << glewGetErrorString(GlewInitResult) << std::endl;
	
	std::cout << "OpenGL Initialized: " << glGetString(GL_VERSION) << std::endl;

	// Init Memory
	// Init Timer
	
	_sceneManager = std::make_unique<SceneManager>();
	_sceneManager->ChangeScene(SceneID::GAME, this);
	
	_inputManager = std::make_unique<InputManager>();
	_inputManager->ChangeControlScheme(_sceneManager->_currentScene->GetControlScheme());

	_renderer = std::make_unique<RenderSystem>();
	_renderer->Initialize();
}

void Engine::Finalize()
{
	delete _window;
	// fin Timer
	// fin Memory
	   
	// fin OpenGL/GLEW/GLFW
	glfwTerminate();
}