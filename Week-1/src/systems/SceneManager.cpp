#include "systems/SceneManager.h"

using namespace cg3d;

SceneManager::SceneManager()
	: _currentScene(nullptr)
{
}

Scene* SceneManager::CreateScene(SceneID id)
{
	Scene* scene = nullptr;

	switch (id)
	{
	case cg3d::SceneID::BASE:
		break;
	default:
		break;
	}

	return scene;
}

SceneManager::~SceneManager()
{
	delete _currentScene;
}

void SceneManager::ChangeScene(SceneID id)
{
	if (_currentScene != nullptr)
		delete _currentScene;

	_currentScene = CreateScene(id);
}