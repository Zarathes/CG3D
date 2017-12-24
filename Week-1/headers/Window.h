#pragma once
#ifndef __WINDOW_H_
#define __WINDOW_H_

// Structs
typedef struct GLFWwindow GLFWwindow;

namespace cg3d {
	class Engine;
	class InputManager;

	class Window
	{
	friend class Engine;
	private:
		int _screenWidth;
		int _screenHeight;

		float _aspect;

		GLFWwindow *_window;

		void OnResize(GLFWwindow* window, int width, int height);
		void SetCurrentContext(InputManager* manager);

	public:
		Window(int width, int height, char* name, bool fullscreen);
		~Window();
	};
}

#endif // !__WINDOW_H_
