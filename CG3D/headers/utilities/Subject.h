#pragma once

namespace cg3d
{
	// Forward Declaration
	class Observer;
	struct Event;

	class Subject
	{
	private:
		std::vector<Observer*> _observers;
	public:
		Subject();
		~Subject();

		void addObserver(Observer* observer);
		void removeObserver(Observer* observer);

		void notify(Event& event);
	};
}