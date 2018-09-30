#pragma once

// Additional includes

namespace cg3d
{
	class Buffer
	{
	private:
		unsigned int _vaoHandle;

		unsigned int _vertexBufferHandle;
		unsigned int _indexBufferHandle;

		unsigned int _indexCount;
	public:
		Buffer();
		~Buffer();

		void bindBuffer();
		void unbindBuffer();

		unsigned int getElementCount();

		void setBufferData(unsigned int mode, unsigned int vertexCount, float* vertices, unsigned int indexCount, unsigned int *indices);
	};
}