#include "entities\CameraEntity.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include "systems/input/InputManager.h"
#include "systems/input/Mouse.h"
#include "systems/input/Keyboard.h"
#include "systems\timer\TimerManager.h"
#include "systems\timer\Timer.h"
#include "data/Events.h"
#include "graphics/Window.h"

#include "worlds/IWorld.h"

#include "components/CameraComponent.h"
#include <GLM\geometric.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\constants.hpp>

// Constants 
#define CAMERA_SENSITIVITY 0.05f
#define CAMERA_SPEED_MULTIPLIER 5

CameraEntity::CameraEntity()
	: _cameraState(Locked)
	, _scrollLevel(10.0f)
	, _direction(0.0f)
	, _horizontalAngle(0.0f)
	, _verticalAngle(0.0f)
{
}
CameraEntity::~CameraEntity()
{
}

void CameraEntity::start()
{
	InputManager::get().getMouse()->addObserver(this);
	InputManager::get().getKeyboard()->addObserver(this);
	InputManager::get().getActiveWindow()->addObserver(this);

	_cameraComp = addComponent<CameraComponent>();
	_cameraComp->setProjectionProperties(60.0f, 0.1f, 2000.0f, FrustrumType::Projection);

	_horizontalAngle = float(_cameraComp->_windowSize.x / 2);
	_verticalAngle = float(_cameraComp->_windowSize.y / 2);
	
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	_cameraComp->_front = glm::vec3(
		cos(_horizontalAngle) * cos(_verticalAngle),
		sin(_verticalAngle),
		sin(_horizontalAngle) * cos(_verticalAngle)
	);

	// Left vector
	_cameraComp->_left = glm::cross(_cameraComp->_front, glm::vec3(0.0f, 1.0f, 0.0f));
	// Up vector : perpendicular to both front and left
	_cameraComp->_up = glm::cross(_cameraComp->_left, _cameraComp->_front);
}

void CameraEntity::onNotify(Event & event)
{
	switch (event._id)
	{
	case EVENT_MOUSE_MOVE:
	{
		EventMouseMovement& e = static_cast<EventMouseMovement&>(event);
		_mousePosition = e._position;
	}
	break;
	case EVENT_MOUSE_CLICK:
	{
		EventMouseClick& e = static_cast<EventMouseClick&>(event);
		int a = e._action;
		switch (e._button)
		{
		case MOUSE_BUTTON_RIGHT:
			if (_cameraState == Locked && e._action == BUTTON_DOWN)
			{
				_cameraState = Moving;
				InputManager::get().getMouse()->toggleCursorVisibility();
				_oldMousePosition = _mousePosition;
				InputManager::get().getMouse()->centerMousePosition();
			}
			else if (_cameraState == Moving && e._action == BUTTON_UP)
			{
				_cameraState = Locked;
				InputManager::get().getMouse()->toggleCursorVisibility();
				InputManager::get().getMouse()->setCursorPosition(_oldMousePosition);
			}
			break;
		default:
			break;
		}
	}
	break;
	case EVENT_MOUSE_SCROLL:
	{
		EventMouseScroll& e = static_cast<EventMouseScroll&>(event);
		_scrollLevel += (e._offset.y * CAMERA_SPEED_MULTIPLIER);
		_scrollLevel = glm::clamp(_scrollLevel, 1.0f, 100.0f);
	}
	break;
	case EVENT_KEYBOARD_INPUT:
	{
		EventKeyboardInput& e = static_cast<EventKeyboardInput&>(event);
		if ((e._action == KEY_DOWN)
			&& _cameraState == Moving)
		{
			switch (e._key)
			{
			case KEY_W:
				_direction.z -= 1.0f;
				break;
			case KEY_S:
				_direction.z += 1.0f;
				break;
			case KEY_A:
				_direction.x += 1.0f;
				break;
			case KEY_D:
				_direction.x -= 1.0f;
				break;
			case KEY_R:
				_direction.y += 1.0f;
				break;
			case KEY_F:
				_direction.y -= 1.0f;
				break;
			default:
				break;
			}
		}

		if ((e._action == KEY_UP)
			&& _cameraState == Moving)
		{
			switch (e._key)
			{
			case KEY_W:
				_direction.z += 1.0f;
				break;
			case KEY_S:
				_direction.z -= 1.0f;
				break;
			case KEY_A:
				_direction.x -= 1.0f;
				break;
			case KEY_D:
				_direction.x += 1.0f;
				break;
			case KEY_R:
				_direction.y -= 1.0f;
				break;
			case KEY_F:
				_direction.y += 1.0f;
				break;
			default:
				break;
			}


		}
	}
	break;

	case EVENT_WINDOW_RESIZE:
	{
		EventWindowResize& e = static_cast<EventWindowResize&>(event);
		_cameraComp->setWindowSize(e._size);
	}
	break;
	default:
		break;
	}
}

void CameraEntity::update()
{
	if (_cameraState == Locked)
		return;

	float delta = TimerManager::get().getTimerByName("engineTimer")->getDeltaTime();
	// Get mouse position
	_mousePosition.x = _mousePosition.x - (_cameraComp->_windowSize.x / 2);
	_mousePosition.y = _mousePosition.y - (_cameraComp->_windowSize.y / 2);

	// Compute new orientation
	_horizontalAngle += float(_mousePosition.x) * CAMERA_SENSITIVITY * delta;
	_verticalAngle += float(_mousePosition.y) * CAMERA_SENSITIVITY * delta;
	InputManager::get().getMouse()->centerMousePosition();

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	_cameraComp->_front = glm::vec3(
		cos(_horizontalAngle) * cos(_verticalAngle),
		sin(_verticalAngle),
		sin(_horizontalAngle) * cos(_verticalAngle)
	);
	
	// Left vector
	_cameraComp->_left = glm::cross(_cameraComp->_front, glm::vec3(0.0f, 1.0f, 0.0f));
	// Up vector : perpendicular to both front and left
	_cameraComp->_up = glm::cross(_cameraComp->_left, _cameraComp->_front);
	
	if (glm::length(_direction) > 0)
	{
		glm::vec3 relativeDirection = glm::mat3(_cameraComp->_left, _cameraComp->_up, _cameraComp->_front) * glm::normalize(_direction);
		glm::vec3 position = getTransform()->getPosition();
		position += relativeDirection * (_scrollLevel * delta);
		getTransform()->setPosition(position);
	}
}