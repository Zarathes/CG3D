#pragma once
#ifndef ENTITY_H_

namespace cg3d {

	// Enumerations
	enum ComType {
		ComInvalid = 0x00,
		ComGraphic = 0x01,
		ComCamera = 0x02,
		//ComCamera  = 0x04,
	};

	// Forward declarations
	class Entity;

	class Component
	{
		friend class Entity;
	public:
		Component() {};
		Component(ComType type) : _type(type) {};
		~Component() {};

		virtual void Initialize(std::shared_ptr<Entity> parent) = 0;
		virtual void Update(float dt) = 0;
		virtual void Finalize() = 0;
	protected:
		ComType _type = ComInvalid;
		std::shared_ptr<Entity> m_parent;
	};

	class Entity
	{
	private:
		unsigned int _count = 0;
		
		bool _isAlive;
		unsigned char _comFlag;
		unsigned int _id = _count;

		std::map<ComType, std::shared_ptr<Component>> _components;
	public:
		Entity();
		~Entity();

		const unsigned int GetId() { return _id; };
		void AddComponent(std::shared_ptr<Component> component);
		std::shared_ptr<Component> GetComponent(ComType type);
		void RemoveComponent(ComType type);
		bool HasComponent(ComType type);
	};
}
#endif // !ENTITY_H_
