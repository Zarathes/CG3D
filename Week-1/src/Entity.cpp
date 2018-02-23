#include "Entity.h"

// Namespaces
using namespace cg3d;

// Additional includes

Entity::Entity()
	: _components(std::map<ComType, std::shared_ptr<Component>>())
	, _isAlive(true)
	, _comFlag(ComInvalid)
	, _id(_count)
{
	_count++;
}
Entity::~Entity()
{

}

void Entity::AddComponent(std::shared_ptr<Component> component)
{
	if (!HasComponent(component->_type))
	{
		_components[component->_type] = component;
		_comFlag += static_cast<unsigned char>(component->_type);
	}
}
std::shared_ptr<Component> Entity::GetComponent(ComType type)
{
	if (HasComponent(type))
	{
		return _components[type];
	}
	return nullptr;
}
void Entity::RemoveComponent(ComType type)
{
	_components.erase(type);
	_comFlag -= static_cast<unsigned char>(type);
}
bool Entity::HasComponent(ComType type)
{
	if(_comFlag & type)
		return true;
	return false;
}
