#include "entities\GraphicsEntity.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "systems\resources\ResourceManager.h"
#include "components\GraphicsComponent.h"
#include "graphics\Mesh.h"

GraphicsEntity::GraphicsEntity()
{
}
GraphicsEntity::~GraphicsEntity()
{
}

void GraphicsEntity::start()
{
	_graphicsComp = addComponent<GraphicsComponent>();
	_graphicsComp->setMesh("chr_knight");
	_graphicsComp->setShader("Basic");
}
void GraphicsEntity::update()
{
}