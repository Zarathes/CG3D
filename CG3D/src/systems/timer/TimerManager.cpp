#include "systems\timer\TimerManager.h"

// Additional includes
#include "systems\timer\Timer.h"

// Namespaces
using namespace cg3d;

TimerManager::TimerManager()
	: _timers(std::map<std::string,Timer*>())
{
}

TimerManager::~TimerManager()
{
	_timers.clear();
}

void TimerManager::update()
{
	std::map<std::string, Timer*>::iterator it = _timers.begin();
	while (it != _timers.end())
	{
		(*it).second->update();
		it++;
	}
}

Timer* TimerManager::getTimerByName(std::string name)
{
	std::map<std::string, Timer*>::iterator it = _timers.find(name);
	if (it == _timers.end())
		return nullptr;
	return (*it).second;
}

bool TimerManager::addTimer(std::string name)
{
	std::map<std::string, Timer*>::iterator it = _timers.find(name);
	if (it != _timers.end())
		return false;
	Timer* timer = new Timer(name);
	timer->start();
	_timers.insert(std::make_pair(name, timer));
	return true;
}

bool TimerManager::removeTimer(std::string name)
{
	std::map<std::string, Timer*>::iterator it = _timers.find(name);
	if (it == _timers.end())
		return false;
	_timers.erase(it);
	return true;
}
