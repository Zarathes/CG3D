#pragma once
#ifndef GRAPHICSCOMPONENT_H_
#define GRAPHICSCOMPONENT_H_

// Additional Includes
#include "Entity.h"

namespace cg3d
{
	// Forward declarations
	class Mesh;

	class GraphicsComponent : public Component
	{
	public:
		glm::vec3		_position;
		glm::vec3		_rotations;
		glm::vec3		_scales;
		Mesh		   *_mesh;

		GraphicsComponent();
		~GraphicsComponent();
		
		void Initialize(std::shared_ptr<Entity> parent);
		void Update(float dt);
		void Finalize();
	private:
	};
}

#endif // !GRAPHICSCOMPONENT_H_
