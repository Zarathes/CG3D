#include "systems/input/InputManager.h"

using namespace cg3d;

// Additional includes
#include "systems/input/Mouse.h"
#include "systems/input/Keyboard.h"
#include "data/Events.h"
#include "graphics/Scene.h"
#include "graphics/Window.h"
#include <algorithm>

InputManager::InputManager()
	: _inputMap(std::map<int, int>())
	, _mouse(new Mouse())
	, _keyboard(new Keyboard())
{
}

InputManager::~InputManager()
{
	delete _mouse;
}

Mouse * cg3d::InputManager::getMouse() const
{
	return _mouse;
}

Keyboard * cg3d::InputManager::getKeyboard() const
{
	return _keyboard;
}

Window * InputManager::getActiveWindow() const
{
	return _activeWindow;
}

void InputManager::onResize(glm::vec2 size)
{
	//std::cout << "Window onResize: width " << size.x << ", height " << size.y << std::endl;
	_windowSize = size;
}
void InputManager::onKeyInput(KeyStroke stroke)
{
	_keyboard->notify(EventKeyboardInput(stroke._key, stroke._action));
}
void InputManager::onMouseMovement(glm::vec2 position)
{
	_mouse->notify(EventMouseMovement(position));
}
void InputManager::onMouseClick(ButtonClick click)
{
	_mouse->notify(EventMouseClick(click._button, click._action));
}
void InputManager::onMouseScroll(glm::vec2 offset)
{
	_mouse->notify(EventMouseScroll(offset));
}

void InputManager::setActiveWindow(Window * window)
{
	_activeWindow = window;
	_mouse->setActiveWindow(_activeWindow);
	_keyboard->setActiveWindow(_activeWindow);
}