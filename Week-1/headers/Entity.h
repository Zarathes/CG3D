#pragma once
#ifndef ENTITY_H_

namespace cg3d {
	enum ComType {
		ComInvalid = 0x00,
		ComGraphic = 0x01,
		ComCamera = 0x02,
		//ComCamera  = 0x04,
	};

	class Component
	{
	friend class Entity;
	public:

	private:
		ComType _type = ComInvalid;
	};

	class Entity
	{
	private:
		bool _isAlive;
		unsigned char _comFlag;

		std::map<ComType, std::shared_ptr<Component>> _components;
	public:
		Entity();
		~Entity();

		void AddComponent(std::shared_ptr<Component> component);
		void RemoveComponent(ComType type);
		bool HasComponent(ComType type);
	};
}
#endif // !ENTITY_H_
