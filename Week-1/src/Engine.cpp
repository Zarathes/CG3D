#include "Engine.h"

// Namespaces
using namespace cg3d;

// Additional Includes

// ----- Main -----
// Entry point of the application
// ----------------
int main()
{
	std::shared_ptr<Engine> app = std::make_shared<Engine>();
	app->GameLoop();
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
		_sceneManager->_currentScene->Redraw(0.16f);
		glfwPollEvents();
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
	
	_window = std::make_shared<Window>(this, 1920, 1080, "CG3D", false);

	if (GLint GlewInitResult = glewInit() != GLEW_OK)
		std::cout << "Error: " << glewGetErrorString(GlewInitResult) << std::endl;
	
	std::cout << "OpenGL Initialized: " << glGetString(GL_VERSION) << std::endl;

	// Init Memory
	// Init Timer
	
	_sceneManager = std::make_unique<SceneManager>();
	_sceneManager->ChangeScene(SceneID::GAME, shared_from_this());
	
	_inputManager = std::make_unique<InputManager>();
	_inputManager->ChangeControlScheme(_sceneManager->_currentScene->GetControlScheme());

	_renderer = std::make_unique<RenderSystem>();
	_renderer->Initialize();
	_window->SetActiveWindow();
	_renderer->_activeWindow = _window;

	_sceneManager->_currentScene->Load();
}

void Engine::Finalize()
{
	// fin Timer
	// fin Memory
	   
	// fin OpenGL/GLEW/GLFW
	glfwTerminate();
}