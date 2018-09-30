#pragma once

// Additional includes
#include "utilities/Subject.h"
#include "utilities/Observer.h"

namespace cg3d
{
	class Window;

	class Mouse : public Subject, Observer
	{
	friend class InputManager;
	private:
		glm::vec2 _windowSize;

		bool isCursorVisible;
		Window* _activeWindow;
	public:
		Mouse();
		~Mouse();

		void onNotify(Event& event);

		void setActiveWindow(Window * window);
		void toggleCursorVisibility();

		void setCursorPosition(glm::vec2 position);
		void centerMousePosition();
	};
}