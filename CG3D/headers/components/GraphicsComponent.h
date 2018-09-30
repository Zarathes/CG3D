#pragma once

// Additional Includes
#include "components\IComponent.h"

namespace cg3d
{
	// Forward declarations
	class Entity;
	class Mesh;
	
	class GraphicsComponent : public IComponent
	{
	private:
		uint64_t _shaderId;
		Mesh* _mesh;
		float _alpha;
	public:		
		GraphicsComponent();
		~GraphicsComponent();
		
		void initialize();
		void update();
		void finalize();

		uint64_t getShaderId() const;
		void setShader(const std::string shaderName);

		Mesh* getMesh() const;
		void setMesh(std::string meshName);

		float getAlpha() const;
	};
}
