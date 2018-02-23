#include "systems/SceneManager.h"

// Namespaces
using namespace cg3d;

#ifndef GAMESCENE_H_
	#include "scenes/GameScene.h"
#endif // !GAMESCENE_H_


SceneManager::SceneManager()
	: _currentScene(nullptr)
{
}

Scene* SceneManager::CreateScene(SceneID id, std::shared_ptr<Engine> delegate)
{
	Scene* scene = nullptr;

	switch (id)
	{
	case SceneID::BASE:
		break;
	case SceneID::GAME:
		scene = new GameScene(delegate);
		break;
	default:
		break;
	}

	return scene;
}

SceneManager::~SceneManager()
{
	if (_currentScene != nullptr)
		delete _currentScene;
}

void SceneManager::ChangeScene(SceneID id, std::shared_ptr<Engine> delegate)
{
	if (_currentScene != nullptr)
		delete _currentScene;

	_currentScene = CreateScene(id, delegate);
}