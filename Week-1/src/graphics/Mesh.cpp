#include "graphics/Mesh.h"

// Namespaces
using namespace cg3d;

// Additional Includes

#ifndef _SHADERPROGAM_H_ 
	#include "graphics/ShaderProgram.h"
#endif // _SHADERPROGRAM_H_

Mesh::Mesh(std::shared_ptr<ShaderProgram> program)
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
	, _program(data.program)
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
}