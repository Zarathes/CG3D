#pragma once
#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#ifndef _glfw3_h_
	#include <GLFW\glfw3.h>
#endif // !_glfw3_h_

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << std::endl;
		return false;
	}
	return true;
}
#endif // !__UTILITIES_H_
