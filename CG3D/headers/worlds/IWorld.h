#pragma once

namespace cg3d
{
	// Forward declare
	class EntityManager;
	class Scene;

	class IWorld : public std::enable_shared_from_this<IWorld>
	{
	protected:
		bool _shouldClose = false;
		WorldID _ID;

		EntityManager* _entityManager;
		Scene*  _scene;
	public:
		virtual void load() = 0;
		virtual void start() = 0;
		virtual void update() = 0;
		virtual void unload() = 0;

		virtual void deleteEntity(std::string name) = 0;

		Scene* getScene() { return _scene; };
		bool shouldClose() { return _shouldClose; };
	};
}