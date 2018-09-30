#pragma once

namespace cg3d 
{
	class IWorld;
	class Entity;
	class Component;

	class EntityManager
	{
	private:
		std::vector<Entity*> _entities;
		std::vector<Entity*> _removeList;

		void markForDelete(Entity* entity);
		void deleteSingle(Entity* entity);
	public:
		EntityManager();
		~EntityManager();
		
		void start();
		void update();

		//add entity to world
		template<typename T, typename ... Args>
		T* addEntity(std::string name, IWorld* world)
		{
			//allocate entity
			T* entity = new T();
			//initialize, not done in constructor because it required childs to implement it
			entity->startBase(world, name);
			//push into vector
			_entities.push_back(entity);
			//return the reference
			return entity;
		}

		void deleteEntity(std::string name);

	};
}