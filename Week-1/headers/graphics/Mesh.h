#pragma once
#ifndef MESH_H_

// Additional includes

namespace cg3d {
	class ShaderProgram;

	struct MeshData
	{
		glm::vec3		position;
		glm::vec3		rotations;
		glm::vec3		scales;
		float			alpha;
		std::shared_ptr<ShaderProgram>	program;
	};

	class Mesh
	{
	friend class GraphicsComponent;
	public:
						Mesh(std::shared_ptr<ShaderProgram> program);
						Mesh(MeshData data);
						~Mesh();
	private:

		GLuint			_vertexCount;
		GLuint			_indexCount;

		GLfloat*		_vertices;
		GLuint*			_indices;

		std::shared_ptr<ShaderProgram> _program;
		
		glm::vec3		_position;
		glm::vec3		_rotations;
		glm::vec3		_scales;
		float			_alpha;

		glm::mat4		_modelMatrix;
	};
}
#endif // !MESH_H_
