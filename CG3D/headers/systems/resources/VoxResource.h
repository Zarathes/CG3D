#pragma once

// Additional includes
#include "systems\resources\Resource.h"
#include <fstream>
#include <unordered_map>

namespace cg3d
{
	// Constants
	const uint32_t MAX_VOXEL_ID = 2000376;
	const uint32_t NO_VOXEL_ID = MAX_VOXEL_ID;

	// Enumerations
	enum MaterialType : int
	{
		TypeDiffuse = 0x00,
		TypeMetal = 0x01,
		TypeGlass = 0x02,
		TypeEmit = 0x03,
	};

	// Structures
	struct VoxelData
	{
	public:
		uint32_t _id = NO_VOXEL_ID;
		uint32_t _matId;
		glm::ivec3 _position;
	};

	struct ModelData
	{
		uint32_t _voxCount;
		glm::ivec3 _size;
		std::vector<VoxelData> _voxelArray;
	};

	struct MaterialData
	{
	public:
		uint32_t _matId;
		MaterialType _type;		
		float _propWeight;
		float _propRough;

		glm::vec4 _diffuseColor;

		float _propSpecular;
		float _propRefraction;
		float _propAttentuate;
		float _propFlux;
		float _propGlow;
		float _propUnit;
		float _propPlastic;
		float padding;		// 4 Bytes

	};
	
	class VoxResource : public Resource
	{
		friend class Mesh;
		friend class RenderSystem;
	private:
		std::unordered_map<std::string, int> _dictionary;

		std::string _name;
		ModelData _model;
		std::vector<MaterialData> _materials;
	public:
		VoxResource();
		~VoxResource();

		bool loadResource(uint64_t id, const char* basePath, const char* filePath);
	
		// Loading methods
		bool openFileStream(std::ifstream* stream, std::string filePath);
		int magicNumber(std::ifstream* stream);

		// Read chunks
		uint32_t readChunk(std::ifstream* stream);
		void readSIZEContent(std::ifstream* stream);
		void readXYZIContent(std::ifstream* stream);
		void readRGBAContent(std::ifstream* stream);
		void readMATLContent(std::ifstream* stream);
	};
}
