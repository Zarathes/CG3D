#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

// Additional includes
#ifndef WINDOW_H_
	#include  "Window.h"
#endif // !WINDOW_H_

#ifndef SCENEMANAGEGER_H_
	#include "systems/SceneManager.h"
#endif // !SCENEMANAGEGER_H_

#ifndef INPUTMANAGER_H_
	#include "systems/InputManager.h"
#endif // !INPUTMANAGER_H_

#ifndef RENDERSYSTEM_H_
	#include "systems/RenderSystem.h"
#endif //!RENDERSYSTEM_H_

namespace cg3d
{

	class Engine
	{

	private:
		Window	     *_window;
		std::unique_ptr<SceneManager> _sceneManager;
		std::unique_ptr<InputManager> _inputManager;
		std::unique_ptr<RenderSystem> _renderer;

		void Initialize();		
		void Finalize();
	public:
		bool _shouldClose;

		Engine();
		~Engine() {};

		void GameLoop();
	};
}
#endif // !ENGINE_H_