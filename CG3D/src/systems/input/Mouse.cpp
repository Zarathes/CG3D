#include "systems/input/Mouse.h"

// Additional includes
#include "graphics/Window.h"
#include "data/Events.h"
// Namespaces
using namespace cg3d;
Mouse::Mouse()
	: isCursorVisible(true)
	, _activeWindow(nullptr)
{
}
Mouse::~Mouse()
{
}

void Mouse::onNotify(Event & event)
{
	switch (event._id)
	{
	case EVENT_WINDOW_RESIZE:
	{
		EventWindowResize& e = static_cast<EventWindowResize&>(event);
		_windowSize = e._size;
	}
	default:
		break;
	}
}

void Mouse::setActiveWindow(Window * window)
{
	if (_activeWindow != nullptr)
		_activeWindow->removeObserver(this);
	_activeWindow = window;
	_activeWindow->addObserver(this);
}

void Mouse::toggleCursorVisibility()
{
	isCursorVisible = !isCursorVisible;
	if(isCursorVisible)	
		glfwSetInputMode(_activeWindow->getWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(_activeWindow->getWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Mouse::setCursorPosition(glm::vec2 position)
{
	glfwSetCursorPos(_activeWindow->getWindowHandle(), position.x, position.y);
	notify(EventMouseMovement(position));
}

void Mouse::centerMousePosition()
{
	glm::vec2 position = { _windowSize.x / 2, _windowSize.y / 2 };
	setCursorPosition(position);
}
