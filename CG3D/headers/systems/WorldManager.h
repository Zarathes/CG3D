#pragma once

// Additional includes

namespace cg3d 
{
	// Forward declaration
	class IWorld;

	class WorldManager
	{
	private:
		IWorld* _currentWorld;

		IWorld* createWorld(WorldID id);
	public:
		WorldManager();
		~WorldManager();

		void changeWorld(WorldID id);
		IWorld* getCurrentWorld();
	};
}