#pragma once

// Additional includes
#include "systems\resources\Resource.h"

namespace cg3d
{	
	struct VoxelGroup
	{
		uint32_t _materialID;
		uint32_t _elementOffset = 0;
		uint32_t _elementCount = 0;

		VoxelGroup(uint32_t materialID)
			: _materialID(materialID)
		{
		}
	};

	class Buffer;

	class Mesh : public Resource
	{
	friend class GraphicsComponent;
	private:

		uint64_t _voxResourceID;
		Buffer* _buffer;
		std::vector<VoxelGroup> _voxelGroups;

		void createCube(uint32_t id, glm::ivec3 coordinates, std::vector<float>* vertices, std::vector<uint32_t>* indeces);
	public:
		Mesh();
		~Mesh();

		uint64_t getVoxResourceID() const;
		Buffer* getBuffer() const;
		std::vector<VoxelGroup> getVoxelGroups() const;

		bool loadResource(uint64_t id, const char* basePath, const char* filePath);
	};
}