#include "graphics\Mesh.h"

// Namespaces
using namespace cg3d;

// Additional Includes
#include "systems\resources\ResourceManager.h"
#include "systems\resources\VoxResource.h"
#include "graphics\Buffer.h"

void Mesh::createCube(uint32_t id, glm::ivec3 coordinates, std::vector<float>* vertices, std::vector<uint32_t>* indeces)
{
	// Vertices
	//vertices->push_back(coordinates.x + -0.5f);
	//vertices->push_back(coordinates.y + 0.5f);
	//vertices->push_back(coordinates.z + 0.5f);

	//vertices->push_back(coordinates.x + -0.5f);
	//vertices->push_back(coordinates.y + -0.5f);
	//vertices->push_back(coordinates.z + 0.5f);

	//vertices->push_back(coordinates.x + 0.5f);
	//vertices->push_back(coordinates.y + 0.5f);
	//vertices->push_back(coordinates.z + 0.5f);

	//vertices->push_back(coordinates.x + 0.5f);
	//vertices->push_back(coordinates.y + -0.5f);
	//vertices->push_back(coordinates.z + 0.5f);

	//vertices->push_back(coordinates.x + 0.5f);
	//vertices->push_back(coordinates.y + 0.5f);
	//vertices->push_back(coordinates.z + - 0.5f);

	//vertices->push_back(coordinates.x + 0.5f);
	//vertices->push_back(coordinates.y + -0.5f);
	//vertices->push_back(coordinates.z + - 0.5f);

	//vertices->push_back(coordinates.x + -0.5f);
	//vertices->push_back(coordinates.y + 0.5f); 
	//vertices->push_back(coordinates.z + - 0.5f);

	//vertices->push_back(coordinates.x + -0.5f);
	//vertices->push_back(coordinates.y + -0.5f);
	//vertices->push_back(coordinates.z + -0.5f);

	// Face #1
	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);
	
	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);
	
	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);

	// Face #2
	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Face #3
	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);

	// Face #4
	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);

	// Face #5
	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + 0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(1.0f);
	vertices->push_back(0.0f);

	// Face #6
	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + 0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + 0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);
	vertices->push_back(0.0f);

	// Position
	vertices->push_back(coordinates.x + -0.5f);
	vertices->push_back(coordinates.y + -0.5f);
	vertices->push_back(coordinates.z + -0.5f);
	// Normal
	vertices->push_back(0.0f);
	vertices->push_back(-1.0f);
	vertices->push_back(0.0f);

	// indeces
	//uint32_t base = id * 8;
	uint32_t base = id * 24;
	// Face #1
	indeces->push_back(base);
	indeces->push_back(base + 2);
	indeces->push_back(base + 1);

	indeces->push_back(base);
	indeces->push_back(base + 3);
	indeces->push_back(base + 2);

	// Face #2
	indeces->push_back(base + 4);
	indeces->push_back(base + 6);
	indeces->push_back(base + 5);
	
	indeces->push_back(base + 4);
	indeces->push_back(base + 7);
	indeces->push_back(base + 6);

	// Face #3
	indeces->push_back(base + 8);
	indeces->push_back(base + 10);
	indeces->push_back(base + 9);

	indeces->push_back(base + 8);
	indeces->push_back(base + 11);
	indeces->push_back(base + 10);

	// Face #4
	indeces->push_back(base + 12);
	indeces->push_back(base + 14);
	indeces->push_back(base + 13);

	indeces->push_back(base + 12);
	indeces->push_back(base + 15);
	indeces->push_back(base + 14);

	// Face #5
	indeces->push_back(base + 16);
	indeces->push_back(base + 17);
	indeces->push_back(base + 18);

	indeces->push_back(base + 16);
	indeces->push_back(base + 18);
	indeces->push_back(base + 19);

	// Face #6
	indeces->push_back(base + 20);
	indeces->push_back(base + 22);
	indeces->push_back(base + 21);

	indeces->push_back(base + 20);
	indeces->push_back(base + 23);
	indeces->push_back(base + 22);
	 
	//indeces->push_back(base + 4);
	//indeces->push_back(base + 7);
	//indeces->push_back(base + 6);
	//
	//indeces->push_back(base + 4);
	//indeces->push_back(base + 5);
	//indeces->push_back(base + 7);
	// 
	//indeces->push_back(base + 6);
	//indeces->push_back(base + 1);
	//indeces->push_back(base);
	//
	//indeces->push_back(base + 6);
	//indeces->push_back(base + 7);
	//indeces->push_back(base + 1);
	//
	//indeces->push_back(base + 6);
	//indeces->push_back(base);
	//indeces->push_back(base + 2);
	//
	//indeces->push_back(base + 6);
	//indeces->push_back(base + 2);
	//indeces->push_back(base + 4);
	//
	//indeces->push_back(base + 7);
	//indeces->push_back(base + 3);
	//indeces->push_back(base + 1); 
	//
	//indeces->push_back(base + 7);
	//indeces->push_back(base + 5);
	//indeces->push_back(base + 3);
}

Mesh::Mesh()
	: Resource(
		ResourceType::RecourceMesh
		, "vox_models\\"
	)
	, _buffer(nullptr)
	, _voxelGroups(std::vector<VoxelGroup>())
{	
}


Mesh::~Mesh()
{
	delete _buffer;
}

uint64_t Mesh::getVoxResourceID() const
{
	return _voxResourceID;
}

Buffer* cg3d::Mesh::getBuffer() const
{
	return _buffer;
}

std::vector<VoxelGroup> Mesh::getVoxelGroups() const
{
	return _voxelGroups;
}

bool Mesh::loadResource(uint64_t id, const char * basePath, const char * filePath)
{
	_id = id;
	_path = filePath;

	VoxResource* resource = ResourceManager::get().getResource<VoxResource>(std::string(filePath) + ".vox");
	if (resource)
	{		
		_voxResourceID = resource->getResourceID();

		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		glm::vec3 posOffset;
		posOffset.x = resource->_model._size.x / 2;
		posOffset.y = 0;
		posOffset.z = resource->_model._size.z / 2;

		uint32_t currentID = resource->_model._voxelArray[0]._matId;
		VoxelGroup currentGroup = VoxelGroup(currentID);
		for (size_t count = 0; count < resource->_model._voxCount; count++)
		{
			VoxelData data = resource->_model._voxelArray[count];
			if (currentID != data._matId)
			{
				currentGroup._elementOffset = indices.size() * sizeof(uint32_t) - currentGroup._elementCount * sizeof(uint32_t);
				_voxelGroups.push_back(currentGroup);
				currentID = data._matId;
				currentGroup = VoxelGroup(currentID);
			}
			createCube(count, static_cast<glm::vec3>(data._position) - posOffset, &vertices, &indices);
			currentGroup._elementCount += 36;
		}
		currentGroup._elementOffset = indices.size() * sizeof(uint32_t) - currentGroup._elementCount * sizeof(uint32_t);
		_voxelGroups.push_back(currentGroup);

		_buffer = new Buffer();
		_buffer->setBufferData(GL_STATIC_DRAW, vertices.size(), &vertices[0], indices.size(), &indices[0]);

		std::cout << "Mesh " << filePath << " created" << std::endl;
		return true;
	}
	std::cout << "Mesh " << filePath << " not created" << std::endl;
	return false;
}

