#pragma once

// Structs
typedef struct GLFWwindow GLFWwindow;

// Additional includes
#include "utilities/Subject.h"

namespace cg3d 
{
	class Window : public Subject
	{
	friend class RenderSystem;
	private:
		GLFWwindow *_windowHandle;
		bool isCurorVisible = true;

	public:
		Window(int width, int height, const char* name, bool fullscreen);
		~Window();

		void start();

		GLFWwindow * getWindowHandle() const;
	};
}
