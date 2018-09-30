#pragma once

// Additional includes
#include "systems\resources\Resource.h"

namespace cg3d 
{
	class ShaderProgram : public Resource
	{
		struct ShaderProgramSource
		{
			std::string	_vertexSource;
			std::string	_fragmentSource;
		};

	public:
		ShaderProgram();
		~ShaderProgram();

		bool loadResource(uint64_t id, const char* basePath, const char* filePath);
		
		void bindShader() const;
		void unbindShader() const;

		void setUniform1i(const std::string& name, const GLint value) const;
		void setUniform1ui(const std::string& name, const GLuint value) const;
		void setUniform1f(const std::string& name, const GLfloat value) const;
		void setUniform3f(const std::string& name, const glm::vec3 vec) const;
		void setUniform4f(const std::string& name, const glm::vec4 vec) const;
		void setUniformMatrixf(const std::string& name, const glm::mat4 mat) const;

		void drawElements(GLenum mode, GLuint count, GLenum type, const GLvoid *indices, const bool isDebug = false) const;

	private:
		GLuint _programHandle;
		GLuint _vertexBufferHandle;
		GLuint _indexBufferHandle;

		ShaderProgramSource parseShader(const std::string& filePath) const;
		GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader);
		GLuint compileShader(GLuint type, const std::string& source) const;
		
		GLint getUniformLocation(const std::string& name) const;
	};
}