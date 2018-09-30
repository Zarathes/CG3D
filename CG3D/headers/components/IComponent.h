#pragma once

namespace cg3d
{
	class IComponent
	{
	friend class Entity;
	protected:
		std::string _name;
		Entity* _owner;
	public:
		IComponent() {};
		~IComponent() {};

		//hidden start function
		void start(Entity* owner, std::string name) 
		{
			_owner = owner;
			_name = name;
			this->initialize();
		};

		virtual void initialize() = 0;
		virtual void update() = 0;
		virtual void finalize() = 0;

		std::string getName() const { return _name; }
		Entity* getOwner() { return _owner; };
	};
}