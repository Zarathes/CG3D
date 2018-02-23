#include "scenes\GameScene.h"

// Namespaces
using namespace cg3d;

// Additional includes
#ifndef ENGINE_H_
	#include "Engine.h"
#endif // !ENGINE_H_

#include "components\GraphicsComponent.h"
#include "systems\EntitySystem.h"
#include "graphics\Mesh.h"
#include "Entity.h"
#include "graphics\ShaderProgram.h"

GameScene::GameScene(std::shared_ptr<Engine> delegate)
	: _deletage(delegate)
	, _entitySystem(std::make_shared<EntitySystem>())
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

	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	std::shared_ptr<GraphicsComponent> graphics = std::make_shared<GraphicsComponent>();
	
	MeshData data = MeshData();
	data.position = glm::vec3(0.0f, 0.0f, 0.0f);
	data.rotations = glm::vec3(0.0f, 0.0f, 0.0f);
	data.scales = glm::vec3(1.0f, 1.0f, 1.0f);
	data.alpha = 1.0f;
	data.program = _deletage->_renderer->_programList["Basic"];
	graphics->_mesh = new Mesh(data);

	entity->AddComponent(graphics);
	_entitySystem->AddEntity(entity);
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
	delta;
}
void GameScene::Redraw(float delta)
{
	_deletage->_renderer->Begin();
	for each (std::shared_ptr<Entity> entity in _entitySystem->GetEntitiesByComponent(ComGraphic))
	{
		entity->GetComponent(ComGraphic)->Update(delta);
	}
	_deletage->_renderer->End();
}
void GameScene::Unload()
{

}