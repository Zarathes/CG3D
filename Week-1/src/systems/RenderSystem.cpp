#include "systems/RenderSystem.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include <gtc/matrix_transform.hpp>

#ifndef WINDOW_H_
	#include  "Window.h"
#endif // !WINDOW_H_

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
	GLCall(glClearColor(0.25f, 0.25f, 0.25f, 1.0f));

	_view = glm::lookAt(glm::vec3(1.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void RenderSystem::Begin()
{

}

void RenderSystem::End()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(_activeWindow->_window);

	/* Poll for and process events */
	glfwPollEvents();
}

void RenderSystem::ChangeFrustrum(int width, int height)
{
	_viewWidth = width;
	_viewHeight = height;
	_viewAspect = (float)_viewWidth / (float)_viewHeight;

	_proj = glm::perspective(glm::radians(60.f), _viewAspect, 0.1f, 100.f);

}