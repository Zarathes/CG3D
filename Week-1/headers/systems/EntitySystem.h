#pragma once
#ifndef ENTITYSYSTEM_H_

namespace cg3d {
	class Entity;
	class Component;

	class EntitySystem
	{
	public:
		EntitySystem();
		~EntitySystem();

		void AddEntity(std::shared_ptr<Entity> entity);
		std::shared_ptr<Entity> GetEntityById(const unsigned int id);
		std::vector<std::shared_ptr<Entity>> GetEntitiesByComponent(int type);
		void RemoveEntity(unsigned int id);
		void RemoveEntity(std::shared_ptr<Entity> entity);
	private:
		std::vector<std::shared_ptr<Entity>> _entities;
	};
}
#endif // !ENTITYSYSTEM_H_
