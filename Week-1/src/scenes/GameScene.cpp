#include "scenes\GameScene.h"

// Namespaces
using namespace cg3d;

// Additional includes
#ifndef ENGINE_H_
	#include "Engine.h"
#endif // !ENGINE_H_

GameScene::GameScene(Engine* delegate)
	: _deletage(delegate)
{
	_ID = SceneID::GAME;

	_keyConfig.push_back(KEY_A);
	_keyConfig.push_back(KEY_D);
	_keyConfig.push_back(KEY_S);
	_keyConfig.push_back(KEY_Q);
	_keyConfig.push_back(KEY_W);
}
GameScene::~GameScene()
{

}

void GameScene::Load()
{

}

//TODO: Map keys to scene specific actions
void GameScene::ProcessInput(std::vector<std::pair<int, int>> input)
{
	for each (std::pair<int, int> keyStroke in input)
	{
		if (keyStroke.second == KEY_PRESS) {
			switch (keyStroke.first)
			{
			case KEY_A:
				break;
			case KEY_D:
				break;
			case KEY_S:
				break;
			case KEY_Q:
				_deletage->_shouldClose = true;
				break;
			case KEY_W:
				break;
			default:
				break;
			}
		}
	}
}

void GameScene::Update(float delta)
{

}
void GameScene::Redraw()
{

}
void GameScene::Unload()
{

}