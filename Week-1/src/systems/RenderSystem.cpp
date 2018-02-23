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
	_view = glm::lookAt(glm::vec3(1.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ChangeFrustrum(1920, 1080);
	GLCall(glClearColor(0.25f, 0.25f, 0.25f, 1.0f));

	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glDepthFunc(GL_LESS));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void RenderSystem::Begin()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	for each (std::pair<const std::string, std::shared_ptr<ShaderProgram>> program in _programList)
	{
		program.second->BindShader();
		program.second->SetUniformMatrixf("view", &_view[0][0]);
		program.second->SetUniformMatrixf("proj", &_proj[0][0]);
	}
}

void RenderSystem::End()
{
	glfwSwapBuffers(_activeWindow->_window);
}

void RenderSystem::ChangeFrustrum(int width, int height)
{
	_viewWidth = width;
	_viewHeight = height;
	_viewAspect = (float)_viewWidth / (float)_viewHeight;
	GLCall(glViewport(0, 0, _viewWidth, _viewHeight));

	_proj = glm::perspective(glm::radians(60.f), _viewAspect, 0.1f, 100.f);

}