#pragma once
#ifndef __SHADERPROGRAM_H_

#ifndef _STRING_
#include <string>
#endif // !_STRING_

#ifndef __glew_h__
#include <glew.h> // OpenGL
#endif __glew_h__

namespace cg3d {
	class ShaderProgram
	{
	public:
		GLuint				_programHandle;
		GLuint				_vertexBufferHandle;
		GLuint				_indexBufferHandle;

							ShaderProgram(const std::string& filepath);
							~ShaderProgram();

		void				BindShader() const;
		void				UnbindShader() const;

		void				SetBufferData(GLuint vertexCount, GLfloat* vertices, GLuint indexCount, GLuint* indices) const;
		
		void				EnableVertexAttributeArray(const GLint loc) const; 
		void				DisableVertexAttributeArray(const std::string& name) const;
		void                SetVertexAttribute(const std::string& name, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const;

		void				SetUniformf(const std::string& name, const GLfloat value) const;
		void				SetUniformMatrixf(const std::string& name, const GLfloat* value) const;

		void				DrawElements(GLenum mode, GLuint count, GLenum type, const GLvoid *indices, const bool isDebug = false) const;

	private:
		struct ShaderProgramSource
		{
			std::string		VertexSource;
			std::string		FragmentSource;
		};

		ShaderProgramSource ParseShader(const std::string& filepath) const;
		GLuint				CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		GLuint				CompileShader(GLuint type, const std::string& source) const;
		
		GLint				GetAttributeLocation(const std::string& name) const;
		GLint				GetUniformLocation(const std::string& name) const;
	};
}
#endif // __SHADERPROGRAM_H_