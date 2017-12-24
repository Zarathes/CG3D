#include "components\GraphicsComponent.h"

// Namespaces;
using namespace cg3d;

GraphicsComponent::GraphicsComponent()
	: _position(glm::vec3(0.0f, 0.0f, 0.0f))
	, _rotations(glm::vec3(0.0f, 0.0f, 0.0f))
	, _scales(glm::vec3(1.0f, 1.0f, 1.0f))
	, _mesh(nullptr)
{

}

GraphicsComponent::~GraphicsComponent()
{

}