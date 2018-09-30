#include "systems/EntityManager.h"

#include "worlds/IWorld.h"
#include "entities/Entity.h"

using namespace cg3d;

EntityManager::EntityManager()
	: _entities(std::vector<Entity*>())
{
}
EntityManager::~EntityManager()
{
	_entities.clear();
}

void EntityManager::markForDelete(Entity* entity)
{
	for (size_t i = 0; i < _removeList.size(); ++i)
	{
		if (_removeList[i] == entity)
			return;
	}

	_removeList.push_back(entity);
}
void EntityManager::deleteSingle(Entity* entity)
{
	for (size_t i = 0; i < _entities.size(); ++i)
	{
		if (_entities[i] == entity)
		{
			_entities.erase(_entities.begin() + i);
			return;
		}
	}
}

void EntityManager::start()
{
	// start entities
	for (size_t i = 0; i < _entities.size(); ++i)
	{
		_entities[i]->start();
	}
}

void EntityManager::update()
{
	// Update entities
	for (size_t i = 0; i < _entities.size(); ++i)
	{
		_entities[i]->updateBase();
	}

	// Delete entities
	Entity* current;
	for (size_t i = 0; i < _removeList.size(); ++i)
	{
		current = _removeList[i];
		if (current)
		{
			deleteSingle(current);
		}
	}
	_removeList.clear();
}
void EntityManager::deleteEntity(std::string name)
{
	size_t hash = std::hash<std::string>{}(name);
	for (size_t i = 0; i < _entities.size(); ++i)
	{
		if (std::hash<std::string>{}(_entities[i]->getName()) == hash)
		{
			markForDelete(_entities[i]);
		}
	}
}