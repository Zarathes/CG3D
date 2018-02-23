#include "components\GraphicsComponent.h"

// Additional includes
#include "Entity.h"
#pragma warning(push)
#pragma warning(disable:4201)
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#pragma warning(pop)
#include "graphics\Mesh.h"
#include "graphics\ShaderProgram.h"

// Namespaces;
using namespace cg3d;

GraphicsComponent::GraphicsComponent()
	: _position(glm::vec3(0.0f, 0.0f, 0.0f))
	, _rotations(glm::vec3(0.0f, 0.0f, 0.0f))
	, _scales(glm::vec3(1.0f, 1.0f, 1.0f))
	, _mesh(nullptr)
	, Component(ComGraphic)
{

}

GraphicsComponent::~GraphicsComponent()
{

}

void GraphicsComponent::Initialize(std::shared_ptr<Entity> parent)
{
	m_parent = parent;
}
void GraphicsComponent::Update(float dt)
{
	_rotations.x = _rotations.y + (10 * dt);
	_rotations.y = _rotations.y + (10 * dt);
	_rotations.z = _rotations.y + (10 * dt);
	_mesh->_alpha = (sin((float)glfwGetTime()) + 1) / 2;

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 rotateYaw = glm::rotate(glm::mat4(1.0f), glm::radians(_rotations.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
	glm::mat4 rotatePitch = glm::rotate(glm::mat4(1.0f), glm::radians(_rotations.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Pitch
	glm::mat4 rotateRoll = glm::rotate(glm::mat4(1.0f), glm::radians(_rotations.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Roll	
	glm::mat4 rotate = rotateYaw * rotatePitch * rotateRoll;
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), _scales);

	glm::mat4 _modelMatrix = translate * rotate * scale;

	_mesh->_program->BindShader();
	_mesh->_program->SetBufferData(_mesh->_vertexCount, _mesh->_vertices, _mesh->_indexCount, _mesh->_indices);

	_mesh->_program->SetUniformMatrixf("model", &_modelMatrix[0][0]);
	_mesh->_program->SetUniformf("alpha", _mesh->_alpha);

	_mesh->_program->SetVertexAttribute("position", 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
	_mesh->_program->SetVertexAttribute("color", 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));

	_mesh->_program->DrawElements(GL_TRIANGLES, _mesh->_indexCount, GL_UNSIGNED_INT, 0, false);

	_mesh->_program->DisableVertexAttributeArray("position");
	_mesh->_program->DisableVertexAttributeArray("color");
}
void GraphicsComponent::Finalize()
{
	m_parent = nullptr;
}