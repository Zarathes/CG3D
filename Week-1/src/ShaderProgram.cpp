#include "ShaderProgram.h"

// Namespaces
using namespace cg3d;

// Additional includes
#ifndef _IOSTREAM_
#include <iostream>
#endif // !_IOSTREAM_

#ifndef _FSTREAM_
#include <fstream>
#endif // !_FSTREAM_

#ifndef _SSTREAM_
#include <sstream>
#endif // !_SSTREAM_

#ifndef __UTILITIES_H_
	#include "Utilities.h"
#endif

// ---------- Constructor -----------
// 
// ----------------------------------
ShaderProgram::ShaderProgram(const std::string& filepath)
{
	ShaderProgramSource source = ParseShader(filepath);
	std::cout << "VERTEX" << std::endl;
	std::cout << source.VertexSource << std::endl;
	std::cout << "FRAGEMENT" << std::endl;
	std::cout << source.FragmentSource << std::endl;
	_programHandle = CreateShader(source.VertexSource, source.FragmentSource);

	GLCall(glGenBuffers(1, &_vertexBufferHandle));
	GLCall(glGenBuffers(1, &_indexBufferHandle));
}
// ---------- Destructor ------------
//
// ----------------------------------
ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteBuffers(1, &_vertexBufferHandle));
	GLCall(glDeleteBuffers(1, &_indexBufferHandle));
	GLCall(glDeleteProgram(_programHandle));
}

// ---------- ParseShader -----------
//
// ----------------------------------
ShaderProgram::ShaderProgramSource ShaderProgram::ParseShader(const std::string& filepath) const
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1,
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[int(type)] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}
// ---------- CreateShader ----------
//
// ----------------------------------
GLuint ShaderProgram::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	//GLint program_linked;
	//glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	//if (program_linked != GL_TRUE)
	//{
	//	GLsizei log_length = 0;
	//	GLchar message[1024];
	//	glGetProgramInfoLog(program, 1024, &log_length, message);
	//	// Write the error to a log
	//	std::cout << message << std::endl;
	//}

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}
// ---------- CompileShader ---------
//
// ----------------------------------
GLuint ShaderProgram::CompileShader(GLuint type, const std::string& source) const
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

void ShaderProgram::BindShader() const
{
	GLCall(glUseProgram(_programHandle));
}
void ShaderProgram::UnbindShader() const
{
	GLCall(glUseProgram(0));
}

void ShaderProgram::SetBufferData(GLuint vertexCount, GLfloat* vertices, GLuint indexCount, GLuint* indices) const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferHandle));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount, vertices, GL_DYNAMIC_DRAW));
	
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandle));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * indexCount, indices, GL_DYNAMIC_DRAW));
}

GLint ShaderProgram::GetAttributeLocation(const std::string& name) const
{
	GLCall(GLint loc = glGetAttribLocation(_programHandle, name.c_str()));
	return loc;
}
void ShaderProgram::EnableVertexAttributeArray(const GLint loc) const
{
	GLCall(glEnableVertexAttribArray(loc));
}
void ShaderProgram::SetVertexAttribute(const std::string& name, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	const GLint loc = GetAttributeLocation(name);
	EnableVertexAttributeArray(loc);
	GLCall(glVertexAttribPointer(loc, size, type, GL_FALSE, stride, offset));
}
void ShaderProgram::DisableVertexAttributeArray(const std::string& name) const
{
	GLCall(glDisableVertexAttribArray(GetAttributeLocation(name)));
}

GLint ShaderProgram::GetUniformLocation(const std::string& name) const
{
	GLCall(GLint loc = glGetUniformLocation(_programHandle, name.c_str()));
	return loc;
}
void ShaderProgram::SetUniformf(const std::string& name, const GLfloat value) const
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}
void ShaderProgram::SetUniformMatrixf(const std::string& name, const GLfloat* value) const
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value));
}

void ShaderProgram::DrawElements(GLenum mode, GLuint count, GLenum type, const GLvoid *indices, const bool isDebug) const
{
	if (isDebug)
	{
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		GLCall(glDisable(GL_CULL_FACE));
	}

	GLCall(glDrawElements(mode, count, type, indices));

	if (isDebug)
	{
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		GLCall(glEnable(GL_CULL_FACE));
	}

}