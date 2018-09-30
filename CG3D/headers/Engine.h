#pragma once

// Additional includes

namespace cg3d
{
	// Forward Declarations
	class WorldManager;
	class InputManager;
	class RenderSystem;

	class Engine
	{
	private:
		WorldManager * _worldManager;

		void initialize();		
		void finalize();
	public:
		RenderSystem * _renderer;

		Engine();
		~Engine() {};

		void gameLoop();
	};
}