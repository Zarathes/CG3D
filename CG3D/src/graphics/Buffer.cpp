#include "graphics/Buffer.h"

// Additional includes
#include "utilities/Utilities.h"

// Namespaces
using namespace cg3d;

Buffer::Buffer()
{
	GlCall(glGenVertexArrays(1, &_vaoHandle));
	GlCall(glGenBuffers(1, &_vertexBufferHandle));
	GlCall(glGenBuffers(1, &_indexBufferHandle));
}
Buffer::~Buffer()
{
	GlCall(glDeleteBuffers(1, &_vertexBufferHandle));
	GlCall(glDeleteBuffers(1, &_indexBufferHandle));
	GlCall(glDeleteVertexArrays(1, &_vaoHandle));
}

void Buffer::bindBuffer()
{
	GlCall(glBindVertexArray(_vaoHandle));
}

void Buffer::unbindBuffer()
{
	GlCall(glBindVertexArray(0));
}

unsigned int Buffer::getElementCount()
{
	return _indexCount;
}

void Buffer::setBufferData(unsigned int mode, unsigned int vertexCount, float * vertices, unsigned int indexCount, unsigned int * indices)
{
	_indexCount = indexCount;

	bindBuffer();
	// VBO
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferHandle));
	GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertices, mode));

	// EBO
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandle));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, mode));

	// position
	GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(0)));
	GlCall(glEnableVertexAttribArray(0));
	// color
	//GlCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, reinterpret_cast<void*>(3 * sizeof(float))));
	//GlCall(glEnableVertexAttribArray(1));
	// normal
	GlCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(3 * sizeof(float))));
	GlCall(glEnableVertexAttribArray(1));

	unbindBuffer();
}
