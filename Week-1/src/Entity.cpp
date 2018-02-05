#include "Entity.h";

// Namespaces
using namespace cg3d;

// Additional includes

Entity::Entity()
	: _components(std::map<ComType, std::shared_ptr<Component>>())
	, _isAlive(true)
	, _comFlag(ComInvalid)
{

}
Entity::~Entity()
{

}

void Entity::AddComponent(std::shared_ptr<Component> component)
{
	if (!HasComponent(component->_type))
	{
		_components[component->_type] = component;
		_comFlag += component->_type;
	}
}
void Entity::RemoveComponent(ComType type)
{
	_components.erase(type);
	_comFlag -= type;
}
bool Entity::HasComponent(ComType type)
{
	if(_comFlag & type)
		return true;
	return false;
}
