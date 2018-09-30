#include "components/GraphicsComponent.h"

// Additional includes
#include "systems\timer\TimerManager.h"
#include "systems\timer\Timer.h"
#include "systems\resources\ResourceManager.h"
#include "worlds\IWorld.h"
#include "entities\Entity.h"
#include "graphics\Mesh.h"
#include "graphics\ShaderProgram.h"
#include "graphics\Scene.h"

// Namespaces;
using namespace cg3d;

GraphicsComponent::GraphicsComponent()
	: _mesh(nullptr)
{

}

GraphicsComponent::~GraphicsComponent()
{
	_owner->getWorld()->getScene()->unregisterComponent(this);
}

void GraphicsComponent::initialize()
{
	_owner->getWorld()->getScene()->registerComponent(this);

}
void GraphicsComponent::update()
{
	float delta = TimerManager::get().getTimerByName("engineTimer")->getDeltaTime();
	Transform* transform = _owner->getTransform();

	glm::vec3 rotations = transform->getRotation();
	rotations.x = rotations.x + delta;
	rotations.y = rotations.y + delta;
	rotations.z = rotations.z + delta;
	//transform->setRotation(rotations);

	_alpha = (sin((float)glfwGetTime()) + 1) / 2;
}
void GraphicsComponent::finalize()
{
	_owner = nullptr;
	_mesh = nullptr;
}

uint64_t GraphicsComponent::getShaderId() const
{
	return _shaderId;
}

void GraphicsComponent::setShader(const std::string shaderName)
{
	ShaderProgram* shader = ResourceManager::get().getResource<ShaderProgram>(shaderName);
	if(shader)
		_shaderId = shader->getResourceID();
}

Mesh* GraphicsComponent::getMesh() const
{
	return _mesh;
}
void GraphicsComponent::setMesh(std::string meshName)
{
	_mesh = ResourceManager::get().getResource<Mesh>(meshName);
}

float GraphicsComponent::getAlpha() const
{
	return _alpha;
}
