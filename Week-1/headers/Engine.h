#pragma once
#ifndef __ENGINE_H_
#define __ENGINE_H_

namespace cg3d
{
	class Window;
	class SceneManager;
	class InputManager;

	class Engine
	{

	private:
		Window	     *_window;
		SceneManager *_sceneManager;
		InputManager *_inputManager;

		void Initialize();		
		void Finalize();
	public:
		Engine() {};
		~Engine() {};

		void GameLoop();
	};
}
#endif // !__ENGINE_H_
