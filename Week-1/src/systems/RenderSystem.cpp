#include "systems/RenderSystem.h"

// Namespaces
using namespace cg3d;

// Additional includes
#ifndef SHADERPROGRAM_H_
	#include "graphics/ShaderProgram.h"
#endif //!SHADERPROGRAM_H_

RenderSystem::RenderSystem()
	: _programList(std::map<std::string, std::shared_ptr<ShaderProgram>>())
{
}
RenderSystem::~RenderSystem() 
{
}

void RenderSystem::Initialize()
{
	_programList["Basic"] = (std::make_shared<ShaderProgram>("res/shaders/Basic.shader"));
}

void RenderSystem::Begin()
{

}

void RenderSystem::End()
{

}