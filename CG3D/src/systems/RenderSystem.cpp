#include "systems/RenderSystem.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "systems\resources\ResourceManager.h"
#include "graphics/Window.h"
#include "graphics/Scene.h"
#include "entities/Entity.h"
#include "components/CameraComponent.h"
#include "components/GraphicsComponent.h"
#include "graphics/Mesh.h"
#include "graphics/Buffer.h"
#include "graphics/ShaderProgram.h"
#include "data/Events.h"
#include "editor/EditorOverlay.h"

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


RenderSystem::RenderSystem()
{
}
RenderSystem::~RenderSystem() 
{
	delete _activeWindow;
}

void RenderSystem::onNotify(Event & event)
{
	switch (event._id)
	{

	case EVENT_WINDOW_RESIZE:
	{
		EventWindowResize& e = static_cast<EventWindowResize&>(event);
		_windowSize = e._size;
	}
	default:
		break;
	}
}

void RenderSystem::initialize()
{
	// Initialize glfw
	if (glfwInit() != GLFW_TRUE)
		std::cout << "Error: failed to intitialize glfw" << std::endl;

	// Make sure to use OpenGL Core Profile 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_activeWindow = new Window(1920, 1080, "CG3D", false);
	_activeWindow->addObserver(this);

	if (GLint GlewInitResult = glewInit() != GLEW_OK)
		std::cout << "Error: " << glewGetErrorString(GlewInitResult) << std::endl;
	
	GlCall(glGenBuffers(1, &_materialSSBO));

	std::cout << "OpenGL Initialized: " << glGetString(GL_VERSION) << std::endl;

	glfwSwapInterval(1);
	GlCall(glClearColor(0.25f, 0.25f, 0.25f, 1.0f));
	GlCall(glEnable(GL_DEPTH_TEST));
	GlCall(glEnable(GL_CULL_FACE));
}

void RenderSystem::start()
{
	_activeWindow->start();
}

void RenderSystem::redraw(Scene* scene)
{
	GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GlCall(glViewport(0, 0, static_cast<int>(_windowSize.x), static_cast<int>(_windowSize.y)));
		
	// Get view
	glm::mat4 view = scene->getActiveCamera()->getViewMatrix();
	// Get projection
	glm::mat4 proj = scene->getActiveCamera()->getProjectionMatrix();
	
	// Geometry pass
	for each (GraphicsComponent* component in scene->getRegisteredComponents())
	{
		// Get Transform
		Transform* transform = component->getOwner()->getTransform();
		// Get Mesh
		Mesh* mesh = component->getMesh();
		// Get Shader
		ShaderProgram* shader = ResourceManager::get().getLoadedResource<ShaderProgram>(component->getShaderId());
		if (!shader)
			return;
		// Get Buffer
		Buffer* buffer = mesh->getBuffer();

		// Bind
		shader->bindShader();
		buffer->bindBuffer();

		VoxResource* voxData = ResourceManager::get().getLoadedResource<VoxResource>(mesh->getVoxResourceID());
		
		// Update material SSBO
		GlCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, _materialSSBO));
		GlCall(glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MaterialData) * voxData->_materials.size(), voxData->_materials.data(), GL_DYNAMIC_DRAW));
		GlCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _materialSSBO));
		GlCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
		
		// Set uniforms
		shader->setUniformMatrixf("model", transform->getModelMatrix());
		shader->setUniformMatrixf("view", view);
		shader->setUniformMatrixf("proj", proj);
		shader->setUniform1f("alpha", component->getAlpha());
		shader->setUniform1f("ambientStrength", 0.1);
		shader->setUniform1f("specularStrength", 0.5);
		shader->setUniform3f("dirLight.position", glm::vec3(50.0f, 25.5f, 20.0f));
		shader->setUniform3f("dirLight.direction", glm::normalize(glm::vec3(50.0f, 25.5f, 20.0f)));
		shader->setUniform3f("dirLight.color", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setUniform3f("viewPos", scene->getActiveCamera()->getOwner()->getTransform()->getPosition());

		// Draw VoxelGroups
		for each (VoxelGroup group in mesh->getVoxelGroups())
		{
			shader->setUniform1ui("materialID", group._materialID);
			shader->drawElements(GL_TRIANGLES, group._elementCount, GL_UNSIGNED_INT, (GLvoid*)group._elementOffset, false);
		}
		// Unbind
		buffer->unbindBuffer();
		shader->unbindShader();
	}
	
	EditorOverlay::get().redraw();
	glfwSwapBuffers(_activeWindow->_windowHandle);
}

Window * RenderSystem::getWindow() const
{
	return _activeWindow;
}