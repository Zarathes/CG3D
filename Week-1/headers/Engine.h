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

	class Engine : public std::enable_shared_from_this<Engine>
	{
	private:
		std::shared_ptr<Window>	      _window;
		std::unique_ptr<SceneManager> _sceneManager;
		std::unique_ptr<InputManager> _inputManager;

		void Initialize();		
		void Finalize();
	public:
		bool _shouldClose;
		std::unique_ptr<RenderSystem> _renderer;

		Engine();
		~Engine() {};

		void GameLoop();
	};
}
#endif // !ENGINE_H_
