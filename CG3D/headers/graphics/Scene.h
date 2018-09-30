#pragma once

// Additional includes
#include <unordered_map>

namespace cg3d
{
	// Forward declaration
	class CameraComponent;
	class GraphicsComponent;
	class ShaderProgram;

	class Scene
	{
	private:
		std::vector<GraphicsComponent*> _graphicsComponents;
		CameraComponent* _activeCamera;

	public:
		Scene();
		~Scene();

		void registerComponent(GraphicsComponent* component);
		void unregisterComponent(GraphicsComponent* component);
		std::vector<GraphicsComponent*> getRegisteredComponents() const;

		void setActiveCamera(CameraComponent* component);
		CameraComponent* getActiveCamera();	
	};
}