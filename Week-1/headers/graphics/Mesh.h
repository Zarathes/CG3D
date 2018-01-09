#pragma once
#ifndef MESH_H_

// Additional includes
#include <glm.hpp>

namespace cg3d {
	class ShaderProgram;

	struct MeshData
	{
		glm::vec3		position;
		glm::vec3		rotations;
		glm::vec3		scales;
		float			alpha;
		ShaderProgram	*program;
	};

	class Mesh
	{
	public:
						Mesh(ShaderProgram *program);
						Mesh(MeshData data);
						~Mesh();

		void			Update(GLfloat dt);
		void			Draw(glm::mat4 viewProjMatrix);
	private:

		GLuint			_vertexCount;
		GLuint			_indexCount;

		GLfloat*		_vertices;
		GLuint*			_indices;

		ShaderProgram	*_program;
		
		glm::vec3		_position;
		glm::vec3		_rotations;
		glm::vec3		_scales;
		float			_alpha;

		glm::mat4		_modelMatrix;
	};
}
#endif // !MESH_H_
