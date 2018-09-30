#pragma once

// Additional Includes
#include "worlds/IWorld.h"
#include "utilities/Observer.h"

namespace cg3d 
{
	class EntityManager;

	class GameWorld : public IWorld, public Observer
	{
	private:
		std::shared_ptr<EntityManager> _EntityManager;

		void onNotify(Event& event);
	public:
		GameWorld();
		~GameWorld();

		void load();
		void start();
		void update();
		void unload();


		void deleteEntity(std::string name);
	};
}