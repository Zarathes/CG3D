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
	friend class RenderSystem;
	private:
		int _screenWidth;
		int _screenHeight;

		float _aspect;

		std::vector<KeyStroke> _rawInput;

		Engine*		_delegate;
		GLFWwindow *_window;

		void OnResize(GLFWwindow* window, int width, int height);
		void CharacterCallback(GLFWwindow* window, KeyStroke stroke);


		void ClearInput();
	public:
		Window(Engine* engine, int width, int height, const char* name, bool fullscreen);
		~Window();
		
		void SetActiveWindow();
		std::vector<KeyStroke> GetRawInput();
	};
}

#endif // !WINDOW_H_
