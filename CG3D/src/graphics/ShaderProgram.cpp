#include "graphics/ShaderProgram.h"

// Namespaces
using namespace cg3d;

// Additional includes
#include <fstream>
#include <sstream>
#include <GLM\gtc\type_ptr.hpp>

// ---------- Constructor -----------
// 
// ----------------------------------
ShaderProgram::ShaderProgram()
	: Resource(
		ResourceType::RecourceShader
		, "shaders\\"
	)
{
	
}
// ---------- Destructor ------------
//
// ----------------------------------
ShaderProgram::~ShaderProgram()
{
	GlCall(glDeleteBuffers(1, &_vertexBufferHandle));
	GlCall(glDeleteBuffers(1, &_indexBufferHandle));
	GlCall(glDeleteProgram(_programHandle));
}

bool ShaderProgram::loadResource(uint64_t id, const char* basePath, const char* filePath)
{
	_id = id;
	_path = filePath;

	std::string path = basePath;
	path.append(_subDir);
	path.append(filePath);
	path.append(".shader");

	ShaderProgramSource source = parseShader(path);
	std::cout << "VERTEX" << std::endl;
	std::cout << source._vertexSource << std::endl;
	std::cout << "FRAGEMENT" << std::endl;
	std::cout << source._fragmentSource << std::endl;
	_programHandle = createShader(source._vertexSource, source._fragmentSource);

	GlCall(glGenBuffers(1, &_vertexBufferHandle));
	GlCall(glGenBuffers(1, &_indexBufferHandle));

	return true;
}

// ---------- ParseShader -----------
//
// ----------------------------------
ShaderProgram::ShaderProgramSource ShaderProgram::parseShader(const std::string& filePath) const
{
	std::ifstream stream(filePath);
	ASSERT(stream.is_open());

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
GLuint ShaderProgram::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GlCall(unsigned int program = glCreateProgram());
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(program, vs));
	GlCall(glAttachShader(program, fs));
	GlCall(glLinkProgram(program));
	GlCall(glValidateProgram(program));

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

	GlCall(glDeleteShader(vs));
	GlCall(glDeleteShader(fs));

	return program;
}
// ---------- CompileShader ---------
//
// ----------------------------------
GLuint ShaderProgram::compileShader(GLuint type, const std::string& source) const
{
	GlCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GlCall(glShaderSource(id, 1, &src, nullptr));
	GlCall(glCompileShader(id));

	int result;
	GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GlCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GlCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

void ShaderProgram::bindShader() const
{
	GlCall(glUseProgram(_programHandle));
}
void ShaderProgram::unbindShader() const
{
	GlCall(glUseProgram(0));
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const
{
	GlCall(GLint loc = glGetUniformLocation(_programHandle, name.c_str()));
	return loc;
}
void ShaderProgram::setUniform1i(const std::string & name, const GLint value) const
{
	GlCall(glUniform1i(getUniformLocation(name), value));
}

void ShaderProgram::setUniform1ui(const std::string & name, const GLuint value) const
{
	GlCall(glUniform1ui(getUniformLocation(name), value));
}
void ShaderProgram::setUniform1f(const std::string& name, const GLfloat value) const
{
	GlCall(glUniform1f(getUniformLocation(name), value));
}
void ShaderProgram::setUniform3f(const std::string & name, const glm::vec3 vec) const
{
	GlCall(glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}
void ShaderProgram::setUniform4f(const std::string & name, const glm::vec4 vec) const
{
	GlCall(glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}

void ShaderProgram::setUniformMatrixf(const std::string& name, const glm::mat4 mat) const
{
	GlCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

void ShaderProgram::drawElements(GLenum mode, GLuint count, GLenum type, const GLvoid *indices, const bool isDebug) const
{
	if (isDebug)
	{
		GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		GlCall(glDisable(GL_CULL_FACE));
	}

	GlCall(glDrawElements(mode, count, type, indices));

	if (isDebug)
	{
		GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		GlCall(glEnable(GL_CULL_FACE));
	}

}