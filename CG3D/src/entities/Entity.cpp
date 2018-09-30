#include "entities/Entity.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "worlds\IWorld.h"

Entity::Entity()
	: _transform(new Transform())
{
}
Entity::~Entity()
{
	std::cout << _name.c_str() << ": destructor" << std::endl;
}

void Entity::startBase(IWorld* world, std::string name)
{
	_world = world;
	_name = name;
	this->start();
}

void Entity::updateBase()
{
	//update the entity itself
	this->update();

	//update all the components
	_componentManager.update();

}

void Entity::start()
{
}

void Entity::update()
{
}

void Entity::destroy()
{
	_world->deleteEntity(_name);
}

std::string Entity::getName() const
{
	return _name;
}

IWorld* Entity::getWorld()
{
	return _world;
}

Transform* Entity::getTransform()
{
	return _transform;
}