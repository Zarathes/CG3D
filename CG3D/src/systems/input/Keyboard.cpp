#include "systems/input/Keyboard.h"

// Additional includes

// Namespaces
using namespace cg3d;
Keyboard::Keyboard()
	: _activeWindow(nullptr)

{
}
Keyboard::~Keyboard()
{
}

void Keyboard::setActiveWindow(Window * window)
{
	_activeWindow = window;
}