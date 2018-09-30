#pragma once

// Additional includes
#include <map>

namespace cg3d {
	class Scene;
	class Window;

	class Mouse;
	class Keyboard;
	class Observer;

	class InputManager
	{
	public:
		static InputManager& get()
		{
			static InputManager _instance;
			return _instance;
		}
	private:	
		Mouse * _mouse = nullptr;
		Keyboard * _keyboard = nullptr;

		Window * _activeWindow;
		glm::vec2 _windowSize;

		std::vector<int> _controlScheme;
		std::vector<KeyStroke> _keyInput;
		std::map<int, int>	_inputMap;

		InputManager();
	public:

		~InputManager();

		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;

		Mouse* getMouse() const;
		Keyboard* getKeyboard() const;
		Window* getActiveWindow() const;

		// Callback events
		void onResize(glm::vec2 size);
		void onKeyInput(KeyStroke stroke);
		void onMouseMovement(glm::vec2 position);
		void onMouseClick(ButtonClick click);
		void onMouseScroll(glm::vec2 offset);
		
		// Update
		void setActiveWindow(Window * window);
	};
}