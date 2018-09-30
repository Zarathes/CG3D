#pragma once

// Additional includes
#include "Transform.h"
#include "systems/ComponentManager.h"

namespace cg3d 
{
	// Forward declarations
	class IWorld;
	class IComponent;
	
	class Entity
	{
	protected:		
		ComponentManager _componentManager;

		std::string _name;
		IWorld* _world;
		Transform* _transform;
	public:
		Entity();
		~Entity();

		template<typename T>
		T* getComponent()
		{
			return _componentManager.getComponent<T>();
		}

		//add component to the entity
		template<typename T>
		T* addComponent()
		{
			return addComponentNamed<T>("");
		}

		//add component to the entity with name
		template<typename T, typename ... Args>
		T* addComponentNamed(std::string name)
		{
			return _componentManager.addComponent<T>(this, name);
		}

		//remove component from entity by name
		//remove happens at end of update
		void removeComponent(std::string name)
		{
			_componentManager.deleteComponent(name);
		}
		
		//hidden start function
		void startBase(IWorld* world, std::string name);
		//update the base of the entity (updates components and transform)
		//also calls virtual update function
		void updateBase();

		virtual void start();
		virtual void update();

		//destroy the entity
		void destroy();

		std::string getName() const;
		IWorld* getWorld();
		Transform* getTransform();

	};
}