#include "systems/WorldManager.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "worlds/IWorld.h"
#include "worlds/GameWorld.h"

WorldManager::WorldManager()
	: _currentWorld(nullptr)
{
}

IWorld* WorldManager::createWorld(WorldID id)
{
	IWorld* world = nullptr;

	switch (id)
	{
	case WorldID::BASE:
		break;
	case WorldID::GAME:
		world = new GameWorld();
		break;
	default:
		break;
	}

	return world;
}

WorldManager::~WorldManager()
{
}

void WorldManager::changeWorld(WorldID id)
{
	_currentWorld = createWorld(id);
	_currentWorld->load();
}

IWorld* WorldManager::getCurrentWorld()
{
	return _currentWorld;
}