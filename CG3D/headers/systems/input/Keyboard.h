#pragma once

// Additional includes
#include "utilities/Subject.h"

namespace cg3d
{
	class Window;

	class Keyboard : public Subject
	{
		friend class InputManager;
	private:
		Window * _activeWindow;
	public:
		Keyboard();
		~Keyboard();
		
		void setActiveWindow(Window * window);
	};
}