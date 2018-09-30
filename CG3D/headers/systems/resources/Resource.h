#pragma once

namespace cg3d
{
	// Enumerations
	enum class ResourceType
	{
		ResourceInvalid = 0x00,
		RecourceMesh = 0x01,
		RecourceShader = 0x02,
		RecourceAudio = 0x03,
		RecourceVox = 0x04
	};

	class Resource
	{
		friend class ResourceManager;

	protected:
		uint64_t _id;
		const char* _subDir;
		const char* _path;
		ResourceType _type;

		Resource()
			: _type(ResourceType::ResourceInvalid)
			, _subDir("")
		{};
		Resource(ResourceType type, const char* subDir)
			: _type(type)
			, _subDir(subDir)
		{};
		virtual ~Resource() {};

	public:
		// Get Functions
		uint64_t getResourceID() { return _id; };
		const char* getSubDir() { return _subDir; };
		const char* getPath() { return _path; };
		ResourceType getType() { return _type; };

		// Load the Resource using the Path given
		virtual bool loadResource(uint64_t id, const char* basePath, const char* filePath) { return false; };
	};
}