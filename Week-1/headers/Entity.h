#pragma once
#ifndef ENTITY_H_

namespace cg3d {
	class Entity
	{
	public:
		Entity();
		~Entity();

		void AddComponent();
		void RemoveComponent();
	private:
		bool _isAlive;
	};
}
#endif // !ENTITY_H_
