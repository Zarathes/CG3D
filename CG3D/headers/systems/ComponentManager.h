#pragma once

namespace cg3d
{
	// Forward declarations
	class IComponent;
	class Entity;

	class ComponentManager
	{
	private:
		std::vector<IComponent*> _components;
		std::vector<IComponent*> _removeList;

		void markForDelete(IComponent* component);
		void deleteSingle(IComponent* component);	
	public:
		ComponentManager();
		~ComponentManager();

		void update();

		//get the first component with type T
		template<typename T>
		T* getComponent()
		{
			T* retPtr = nullptr;
			for (size_t i = 0; i < _components.size(); ++i)
			{
				retPtr = (T*)(_components[i]);
				if (retPtr)
				{
					return retPtr;
				}
			}
			//return empty ref
			return nullptr;
		}

		//get the first component with type T and name "name"
		template<typename T>
		T* getComponent(std::string name)
		{
			T> retPtr = nullptr;
			for (size_t i = 0; i < _components.size(); ++i)
			{
				retPtr = std::reinterpret_pointer_cast<T>(_components[i]);
				if (retPtr)
				{
					if (std::hash<std::string>{}(_components[i]->getName()) == hash)
					{
						return retPtr;
					}
				}
			}
			//return empty ref
			return nullptr;
		}

		//add a component to the container
		template<typename T>
		T* addComponent(Entity* owner, std::string name)
		{
			//create/allocate component
			T* component = new T();
			//setup component
			component->start(owner, name);			
			//add to vector
			_components.push_back(component);
			//return the value
			return component;
		}
			
		void deleteComponent(std::string name);
	};
}