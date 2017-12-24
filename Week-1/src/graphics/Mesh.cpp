#include "graphics/Mesh.h"

// Namespaces
using namespace cg3d;

// Additional Includes
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#ifndef _SHADERPROGAM_H_ 
	#include "graphics/ShaderProgram.h"
#endif // _SHADERPROGRAM_H_

#ifndef __UTILITIES_H_
	#include "Utilities.h"
#endif // __UTILITIES_H_

Mesh::Mesh(ShaderProgram *program)
	: _program(program)
{
	_vertexCount = 48;
	_indexCount = 36;

	_vertices = new GLfloat[_vertexCount]{
		//-0.5f,  0.5f, 0.5f, // Position
		//1.0f,  0.0f,  0.0f, // Color

		//-0.5f, -0.5f, 0.5f,
		//0.0f,  1.0f,  0.0f,

		//0.5f,  0.5f, 0.5f,
		//0.0f,  0.0f,  1.0f,

		//0.5f, -0.5f,  0.5f,
		//1.0f,  1.0f,  0.0f,

		//0.5f,  0.5f, -0.5f,
		//0.0f,  1.0f,  1.0f,

		//0.5f,  -0.5f, -0.5f,
		//1.0f,  0.0f,  1.0f,

		//-0.5f,  0.5f, -0.5f,
		//0.0f, 0.0f, 0.0f,

		//-0.5f, -0.5f, -0.5f,
		//1.0f, 1.0f, 1.0f,

		  0.0f,  1.0f,  0.5f,
		1.0f,  0.0f,  0.0f,

		0.0f, -0.5f,  0.5f,
		0.0f,  1.0f,  0.0f,

		-1.0f, -1.0f,  0.5f,
		0.0f,  0.0f,  1.0f,

		1.0f, -1.0f,  0.5f,
		1.0f,  1.0f,  0.0f,

		0.0f,  1.0f, -0.5f,
		1.0f,  0.0f,  1.0f,

		0.0f, -0.5f, -0.5f,
		0.0f,  1.0f,  1.0f,

		1.0f, -1.0f, -0.5f,
		1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f, -0.5f,
		0.0f,  0.0f,  0.0f, 
	};
	_indices = new GLuint[_indexCount] {
		//0, 3, 2,
		//0, 1, 3,

		//2, 5, 4,
		//2, 3, 5,

		//4, 7, 6,
		//4, 5, 7,

		//6, 1, 0,
		//6, 7, 1,

		//6, 0, 2,
		//6, 2, 4,

		//7, 3, 1,
		//7, 5, 3,

		0, 2, 1,
		0, 1, 3,

		4, 6, 5,
		4, 5, 7,

		0, 4, 2,
		4, 7, 2,

		0, 6, 4,
		0, 3, 6,

		2, 7, 5,
		2, 5, 1,

		3, 5, 6,
		3, 1, 5,
	};

	_position = glm::vec3(0.0f, 1.0f, 0.0f);
	_rotations = glm::vec3(0.0f, 0.0f, 0.0f);
	_scales = glm::vec3(2.0f, 2.0f, 2.0f);
	_alpha = 1.0f;
}

Mesh::Mesh(MeshData data)
	: _position(data.position)
	, _rotations(data.rotations)
	, _scales(data.scales)
	, _alpha(data.alpha)
{	
	_program = new cg3d::ShaderProgram("res/shaders/Basic.shader");
	
	_vertexCount = 48;
	_indexCount = 36;

	_vertices = new GLfloat[_vertexCount]{
		//-0.5f,  0.5f, 0.5f, // Position
		//1.0f,  0.0f,  0.0f, // Color

		//-0.5f, -0.5f, 0.5f,
		//0.0f,  1.0f,  0.0f,

		//0.5f,  0.5f, 0.5f,
		//0.0f,  0.0f,  1.0f,

		//0.5f, -0.5f,  0.5f,
		//1.0f,  1.0f,  0.0f,

		//0.5f,  0.5f, -0.5f,
		//0.0f,  1.0f,  1.0f,

		//0.5f,  -0.5f, -0.5f,
		//1.0f,  0.0f,  1.0f,

		//-0.5f,  0.5f, -0.5f,
		//0.0f, 0.0f, 0.0f,

		//-0.5f, -0.5f, -0.5f,
		//1.0f, 1.0f, 1.0f,

		0.0f,  1.0f,  0.5f,
		1.0f,  0.0f,  0.0f,

		0.0f, -0.5f,  0.5f,
		0.0f,  1.0f,  0.0f,

		-1.0f, -1.0f,  0.5f,
		0.0f,  0.0f,  1.0f,

		1.0f, -1.0f,  0.5f,
		1.0f,  1.0f,  0.0f,

		0.0f,  1.0f, -0.5f,
		1.0f,  0.0f,  1.0f,

		0.0f, -0.5f, -0.5f,
		0.0f,  1.0f,  1.0f,

		1.0f, -1.0f, -0.5f,
		1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f, -0.5f,
		0.0f,  0.0f,  0.0f,
	};
	_indices = new GLuint[_indexCount]{
		//0, 3, 2,
		//0, 1, 3,

		//2, 5, 4,
		//2, 3, 5,

		//4, 7, 6,
		//4, 5, 7,

		//6, 1, 0,
		//6, 7, 1,

		//6, 0, 2,
		//6, 2, 4,

		//7, 3, 1,
		//7, 5, 3,

		0, 2, 1,
		0, 1, 3,

		4, 6, 5,
		4, 5, 7,

		0, 4, 2,
		4, 7, 2,

		0, 6, 4,
		0, 3, 6,

		2, 7, 5,
		2, 5, 1,

		3, 5, 6,
		3, 1, 5,
	};
}

Mesh::~Mesh()
{
	delete _program;
}

void Mesh::Update(GLfloat dt)
{
	_rotations.x = _rotations.y + (10 * dt);
	_rotations.y = _rotations.y + (10 * dt);
	_rotations.z = _rotations.y + (10 * dt);
	//_alpha = (sin((float)glfwGetTime()) + 1) / 2;

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 rotateYaw = glm::rotate(glm::mat4(1.0f), glm::radians(_rotations.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
	glm::mat4 rotatePitch = glm::rotate(glm::mat4(1.0f), glm::radians(_rotations.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Pitch
	glm::mat4 rotateRoll = glm::rotate(glm::mat4(1.0f), glm::radians(_rotations.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Roll	
	glm::mat4 rotate = rotateYaw * rotatePitch * rotateRoll;
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), _scales);

	_modelMatrix = translate * rotate * scale;
}
void Mesh::Draw(glm::mat4 viewProjMatrix)
{
	_program->BindShader();
	_program->SetBufferData(_vertexCount, _vertices, _indexCount, _indices);

	glm::mat4 MVP = viewProjMatrix * _modelMatrix;
	_program->SetUniformMatrixf("MVP", &MVP[0][0]);
	_program->SetUniformf("alpha", _alpha);

	_program->SetVertexAttribute("position", 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
	_program->SetVertexAttribute("color", 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));

	_program->DrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0, true);

	_program->DisableVertexAttributeArray("position");
	_program->DisableVertexAttributeArray("color");
}
