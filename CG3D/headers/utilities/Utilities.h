#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) GLClearError();\
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

// Helper functions
uint64_t constexpr mix(char m, uint64_t s)
{
	return ((s << 7) + ~(s >> 3)) + ~m;
}
uint64_t constexpr hash(const char * m)
{
	return (*m) ? mix(*m, hash(m + 1)) : 0;
}