#include "systems\EntitySystem.h"

#include "Entity.h"

using namespace cg3d;

EntitySystem::EntitySystem()
	: _entities(std::vector<std::shared_ptr<Entity>>())
{

}
EntitySystem::~EntitySystem()
{
	_entities.clear();
}

void EntitySystem::AddEntity(std::shared_ptr<Entity> entity)
{
	_entities.push_back(entity);
}
std::shared_ptr<Entity> EntitySystem::GetEntityById(const unsigned int id)
{
	for each (std::shared_ptr<Entity> entity in _entities)
	{
		if (entity->GetId() == id)
			return entity;
	}

	return nullptr;
}
std::vector<std::shared_ptr<Entity>> EntitySystem::GetEntitiesByComponent(int type)
{
	std::vector<std::shared_ptr<Entity>> results = std::vector<std::shared_ptr<Entity>>();

	for each (std::shared_ptr<Entity> entity in _entities)
	{
		if(entity->HasComponent(static_cast<ComType>(type)))
		{
			results.push_back(entity);
		}
	}
	return results;
}
void EntitySystem::RemoveEntity(unsigned int id)
{
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities.at(i)->GetId() == id) {
			_entities.erase(_entities.begin() + i);
			return;
		}
	}
}
void EntitySystem::RemoveEntity(std::shared_ptr<Entity> entityToRemove)
{
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities.at(i) == entityToRemove) {
			_entities.erase(_entities.begin()+i);
			return;
		}			
	}
}