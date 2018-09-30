#include "utilities/Subject.h"

// Adittional includes
#include "utilities/Observer.h"

// Namespaces
using namespace cg3d;

Subject::Subject()
	: _observers(std::vector<Observer*>())
{

}
Subject::~Subject()
{
	_observers.clear();
}

void Subject::addObserver(Observer* observer)
{
	_observers.push_back(observer);
}
void Subject::removeObserver(Observer* observer)
{
	std::vector<Observer*>::iterator it = _observers.begin();
	while (it != _observers.end())
	{
		if (&(*it) == &observer)
		{
			_observers.erase(it);
			return;
		}
		it++;
	}
}

void Subject::notify(Event& event)
{
	for each (Observer* observer in _observers)
	{
		observer->onNotify(event);
	}
}