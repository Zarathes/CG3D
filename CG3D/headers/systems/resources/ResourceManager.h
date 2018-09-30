#pragma once

//Additional includes
#include "systems\resources\Resource.h"
#include "systems\resources\VoxResource.h"
#include <unordered_map>
namespace cg3d
{
	// Forward declaration
	class Resource;

	class ResourceManager
	{
	public:
		static ResourceManager& get()
		{
			static ResourceManager _instance;
			return _instance;
		}
	private:
		const char* _baseDir = "res\\";

		ResourceManager() {};
		std::unordered_map<uint64_t, Resource*> _resources;
	public:
		~ResourceManager();

		// Try to find a resource that is already loaded
		template<typename R>
		R* getLoadedResource(uint64_t id);

		// Return a ResourceRef
		template<typename R>
		R* getResource(std::string path);
	};

	template<typename R>
	R* ResourceManager::getLoadedResource(uint64_t id)
	{
		std::unordered_map<uint64_t, Resource*>::iterator it = _resources.find(id);

		// Return Resource if Found
		if (it != _resources.end())
		{
			return dynamic_cast<R*>((*it).second);
		}

		return nullptr;
	}

	template<typename R>
	R* ResourceManager::getResource(std::string path)
	{
		static_assert(std::is_base_of<Resource, R>::value, "Trying to Get a Non-Resource as a Resource");

		// Check if Resource is already loaded
		uint64_t id = hash(path.c_str());
		R* resource = getLoadedResource<R>(id);

		// Return if Resource was already Loaded
		if (resource != nullptr)
		{
			return resource;
		}

		// Create new Resource and return ref
		resource = new R();
		if (resource->loadResource(id, _baseDir, path.c_str()))
		{
			// Add Resource to Map
			_resources.insert(std::make_pair(id, resource));

			return resource;
		}

		// Loading Failed
		return resource;

	};
}