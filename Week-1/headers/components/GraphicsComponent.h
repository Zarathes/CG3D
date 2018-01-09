#pragma once
#ifndef GRAPHICSCOMPONENT_H_
#define GRAPHICSCOMPONENT_H_

// Additional Includes
#include <glm.hpp>

namespace cg3d
{
	// Forward declarations
	class Mesh;

	class GraphicsComponent
	{
	public:
		glm::vec3		_position;
		glm::vec3		_rotations;
		glm::vec3		_scales;
		Mesh		   *_mesh;

		GraphicsComponent();
		~GraphicsComponent();
	private:
	};
}

#endif // !GRAPHICSCOMPONENT_H_
