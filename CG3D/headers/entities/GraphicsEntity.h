#pragma once

// Additional includes
#include "entities/Entity.h"

namespace cg3d
{
	class GraphicsComponent;


	class GraphicsEntity : public Entity
	{
	private:
		GraphicsComponent* _graphicsComp;
	public:
		GraphicsEntity();
		~GraphicsEntity();

		void start();
		void update();
	};
}