#include "worlds\GameWorld.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "systems\input\InputManager.h"
#include "systems\input\Keyboard.h"
#include "systems\EntityManager.h"
#include "editor\EditorOverlay.h"

#include "data\Events.h"
#include "graphics\Scene.h"
#include "entities\CameraEntity.h"
#include "entities\GraphicsEntity.h"
#include "components\GraphicsComponent.h"

GameWorld::GameWorld()
{
	_ID = WorldID::GAME;
	InputManager::get().getKeyboard()->addObserver(this);
}
GameWorld::~GameWorld()
{

}

void GameWorld::onNotify(Event & event)
{
	switch (event._id)
	{
	case EVENT_KEYBOARD_INPUT:
	{
		EventKeyboardInput& e = static_cast<EventKeyboardInput&>(event);
		if (e._action == KEY_DOWN)
		{
			switch (e._key)
			{
			case KEY_Q:
				_shouldClose = true;
				break;
			default:
				break;
			}
		}
	}
		break;
	default:
		break;
	}
}

void GameWorld::load()
{
	_entityManager = new EntityManager();
	_scene = new Scene();


	CameraEntity* camera = _entityManager->addEntity<CameraEntity>("ActiveCamera", this);
	camera->getTransform()->setPosition({ 50.0f, 12.5f, 0.0f });
	_scene->setActiveCamera(camera->getComponent<CameraComponent>());

	GraphicsEntity* entity;

	entity = _entityManager->addEntity<GraphicsEntity>("Floor", this);
	entity->getTransform()->setPosition({ 0.0f, 0.0f, 0.0f });
	entity->getComponent<GraphicsComponent>()->setMesh("Floor");
	
	entity = _entityManager->addEntity<GraphicsEntity>("GraphicsObject2", this);
	entity->getTransform()->setPosition({ 10.0f, 0.0f, 0.0f });
	entity->getComponent<GraphicsComponent>()->setMesh("chr_knight");

	entity = _entityManager->addEntity<GraphicsEntity>("GraphicsObject3", this);
	entity->getTransform()->setPosition({ 20.0f, 0.0f, 0.0f });
	entity->getComponent<GraphicsComponent>()->setMesh("chr_old");
	
	entity = _entityManager->addEntity<GraphicsEntity>("GraphicsObject4", this);
	entity->getTransform()->setPosition({ -20.0f, 0.0f, 0.0f });
	entity->getComponent<GraphicsComponent>()->setMesh("chr_rain");

	entity = _entityManager->addEntity<GraphicsEntity>("GraphicsObject5", this);
	entity->getTransform()->setPosition({ -10.0f, 0.0f, 00.0f });
	entity->getComponent<GraphicsComponent>()->setMesh("chr_sword");
/*
	entity = _entityManager->addEntity<GraphicsEntity>("GraphicsObject6", this);
	entity->getTransform()->setPosition({ 0.0f, 0.0f, 10.0f });*/
}

void GameWorld::start()
{
}

void GameWorld::update()
{
	_entityManager->update();
}

void GameWorld::unload()
{
	delete _scene;
	delete _entityManager;
}

void GameWorld::deleteEntity(std::string name)
{
	_entityManager->deleteEntity(name);
}
