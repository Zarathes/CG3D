#include "graphics/Scene.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "components/CameraComponent.h"
#include "components/GraphicsComponent.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Window.h"

Scene::Scene()
	: _graphicsComponents(std::vector<GraphicsComponent*>())
	, _activeCamera(nullptr)
{
}

Scene::~Scene()
{
	// Think about where to delete the actual shader from the GPU
	// m_loadedShaders.clear();
}

std::vector<GraphicsComponent*> Scene::getRegisteredComponents() const
{
	return _graphicsComponents;
}
void Scene::registerComponent(GraphicsComponent* component)
{
	_graphicsComponents.push_back(component);
}
void Scene::unregisterComponent(GraphicsComponent* component)
{
	std::vector<GraphicsComponent*>::iterator itr = _graphicsComponents.begin();
	for (; itr != _graphicsComponents.end(); itr++)
	{
		if ((*itr) == component)
		{
			_graphicsComponents.erase(itr);
			break;
		}
	}
}

CameraComponent* Scene::getActiveCamera()
{
	return _activeCamera;
}
void Scene::setActiveCamera(CameraComponent* component)
{
	_activeCamera = component;
}