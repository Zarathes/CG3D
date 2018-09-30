#include "systems/ComponentManager.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "components\IComponent.h"

ComponentManager::ComponentManager()
	: _components(std::vector<IComponent*>())
{
}
ComponentManager::~ComponentManager()
{
	_components.clear();
}

void ComponentManager::markForDelete(IComponent* component)
{
	for (size_t i = 0; i < _removeList.size(); ++i)
	{
		if (_removeList[i] == component)
			return;
	}

	_removeList.push_back(component);
}
void ComponentManager::deleteSingle(IComponent* component)
{
	for (size_t i = 0; i < _components.size(); ++i)
	{
		if (_components[i] == component)
		{
			_components.erase(_components.begin() + i);
			return;
		}
	}
}

void ComponentManager::update()
{
	// Update components
	for (size_t i = 0; i < _components.size(); ++i)
	{
		_components[i]->update();
	}

	// Delete components
	IComponent* current;
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

void ComponentManager::deleteComponent(std::string name)
{
	size_t hash = std::hash<std::string>{}(name);
	for (size_t i = 0; i < _components.size(); ++i)
	{
		if (std::hash<std::string>{}(_components[i]->getName()) == hash)
		{
			markForDelete(_components[i]);
		}
	}
}