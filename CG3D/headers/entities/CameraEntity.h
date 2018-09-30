#pragma once

// Additional includes
#include "entities/Entity.h"
#include "utilities/Observer.h"

namespace cg3d
{
	class CameraComponent;

	enum CameraState
	{
		Locked,
		Moving
	};

	class CameraEntity : public Entity, public Observer
	{
	friend class Subject;
	private:
		CameraState _cameraState;
		float _scrollLevel;
		glm::vec2 _mousePosition;
		glm::vec2 _oldMousePosition;

		glm::vec3 _direction;
		float _horizontalAngle;
		float _verticalAngle;

		CameraComponent* _cameraComp;

		void onNotify(Event& event);
	public:
		CameraEntity();
		~CameraEntity();

		void start();
		void update();
	};
}