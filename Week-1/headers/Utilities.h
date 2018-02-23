#pragma once
#ifndef UTILITIES_H_
#define UTILITIES_H_

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
		std::cout << file << " " << line << ": OpenGL Error (" << error << "): " << function << std::endl;
		return false;
	}
	return true;
}
#endif // !UTILITIES_H_
