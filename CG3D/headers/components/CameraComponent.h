#pragma once

// Additional Includes
#include "components\IComponent.h"

namespace cg3d
{
	// Enumerations
	enum class FrustrumType
	{
		Invalid,
		Projection,
		Orthogonal
	};

	// Forward declarations
	class Entity;

	class CameraComponent : public IComponent
	{		
	friend class CameraEntity;
	private:
		glm::vec3 _up;
		glm::vec3 _front;
		glm::vec3 _left;
		glm::vec3 _target;

		float _fov;
		float _zNear;
		float _zFar;
		FrustrumType _frustrumType;

		glm::vec2 _windowSize;
		glm::mat4 _view;
		glm::mat4 _proj;

	public:
		CameraComponent();
		~CameraComponent();

		void initialize();
		void update();
		void finalize();

		void setProjectionProperties(float fov, float zNear, float zFar, FrustrumType type);

		void setFov(float fov);
		float getFov() const;

		void setZNear(float zNear);
		float getZNear() const;

		void setZFar(float zFar);
		float getZFar() const;

		void setWindowSize(glm::vec2 windowSize);

		void setFrustrumType(FrustrumType type);
		FrustrumType getFrustrumType() const;
		void changeFrustrum();

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
	};
}