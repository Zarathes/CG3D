#pragma once
#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#ifndef SCENEMANAGEGER_H_
	#include "systems/SceneManager.h"
#endif // !SCENEMANAGEGER_H_

namespace cg3d 
{
	class Engine;
	class EntitySystem;

	class GameScene : public Scene
	{
	private:
		std::shared_ptr<Engine>		_deletage;
		std::shared_ptr<EntitySystem> _entitySystem;
	public:
		GameScene(std::shared_ptr<Engine> delegate);
		~GameScene();

		void Load();
		void ProcessInput(std::vector<std::pair<int, int>> input);
		void Update(float delta);
		void Redraw(float delta);
		void Unload();
	};
}

#endif // !GAMESCENE_H_