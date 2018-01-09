#pragma once
#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#ifndef SCENEMANAGEGER_H_
	#include "systems/SceneManager.h"
#endif // !SCENEMANAGEGER_H_

namespace cg3d 
{
	class Engine;

	class GameScene : public Scene
	{
	private:
		Engine		*_deletage;
	public:
		GameScene(Engine* delegate);
		~GameScene();

		void Load();
		void ProcessInput(std::vector<std::pair<int, int>> input);
		void Update(float delta);
		void Redraw();
		void Unload();
	};
}

#endif // !GAMESCENE_H_