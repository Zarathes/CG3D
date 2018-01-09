#pragma once
#ifndef WINDOW_H_
#define WINDOW_H_

// Structs
typedef struct GLFWwindow GLFWwindow;

// Additional includes


namespace cg3d {
	class Engine;

	class Window
	{
	friend class Engine;
	private:
		int _screenWidth;
		int _screenHeight;

		float _aspect;

		std::vector<KeyStroke> _rawInput;
		GLFWwindow *_window;

		void OnResize(GLFWwindow* window, int width, int height);
		void CharacterCallback(GLFWwindow* window, KeyStroke stroke);

		void SetCurrentContext();

		std::vector<KeyStroke> GetRawInput();
		void ClearInput();

	public:
		Window(int width, int height, char* name, bool fullscreen);
		~Window();
	};
}

#endif // !WINDOW_H_
