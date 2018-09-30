#include "Engine.h"

// Namespaces
using namespace cg3d;

// Additional Includes
#include "editor/EditorOverlay.h"
#include "systems/WorldManager.h"
#include "systems/timer/TimerManager.h"
#include "systems/timer/Timer.h"
#include "systems/input/InputManager.h"
#include "systems/resources/ResourceManager.h"
#include "graphics\Mesh.h"
#include "systems/RenderSystem.h"
#include "worlds/IWorld.h"
#include "graphics/Window.h"
#include "graphics/Scene.h"

#include <ctime>

// ----- Main -----
// Entry point of the application
// ----------------
int main()
{
	Engine* app = new Engine();
	app->gameLoop();
	delete app;
}

Engine::Engine()
{
}

// ----- GameLoop -----
// Core of the engine
// It handles set up, shutdown and
// everything in between.
// --------------------
void Engine::gameLoop()
{
	initialize();
	while (!_worldManager->getCurrentWorld()->shouldClose())
	{
		TimerManager::get().update();
		IWorld* currentWorld = _worldManager->getCurrentWorld();
		glfwPollEvents();
		currentWorld->update();
		EditorOverlay::get().update();
		_renderer->redraw(currentWorld->getScene());
	}
	finalize();
}

// ----- Initialize -----
// This method sets up all needed systems 
// and variables. 
// ----------------------
void Engine::initialize()
{
	// Init Memory
	TimerManager::get().addTimer("engineTimer");
	
	_renderer = new RenderSystem();
	_renderer->initialize();
	InputManager::get().setActiveWindow(_renderer->getWindow());
	
	_worldManager = new WorldManager();
	_worldManager->changeWorld(WorldID::GAME);
	
	_renderer->start();
	_worldManager->getCurrentWorld()->start();
	EditorOverlay::get().start(_renderer->getWindow());
}

void Engine::finalize()
{
	delete _worldManager;
	delete _renderer;
	// fin Timer
	// fin Memory
	   
	// fin OpenGL/GLEW/GLFW
	glfwTerminate();
}