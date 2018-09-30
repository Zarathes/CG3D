#include "systems\timer\Timer.h"

// Additional includes 
#include <chrono>

// Namespaces
using namespace cg3d;

// Defines
typedef std::chrono::high_resolution_clock chronos;
typedef chronos::time_point time_point;

Timer::Timer(std::string name)
	: _isRunning(false)
	, _name(name)
	, _deltaTime(0.0f)
	, _baseTime(0)
	, _pauseTime(0)
	, _stopTime(0)
	, _prevTime(0)
{
}

Timer::~Timer()
{
}

void Timer::update()
{
	if (!_isRunning) {
		_deltaTime = 0.0;
		return;
	}
	uint32_t currTime = static_cast<uint32_t>(chronos::now().time_since_epoch() / std::chrono::milliseconds(1));
	//Time difference between this frame and the previous one
	_deltaTime = (currTime - _prevTime) / 1000.0f;

	//Prepare the next frame
	_prevTime = currTime;
	if (_deltaTime < 0.0f) {
		_deltaTime = 0.0f;
	}
}

void Timer::start()
{
	uint32_t startTime = static_cast<uint32_t>(chronos::now().time_since_epoch() / std::chrono::milliseconds(1));
	_prevTime = startTime;
	//If we are resuming the timer from a stopped state
	if (!_isRunning) {
		//Then accumulate the paused time
		_pauseTime += (startTime - _stopTime);
		//Since we are starting the timer back up,
		//the current previous time is not valid,
		//as it occured while paused,
		//so reset it to the current time
		_prevTime = startTime;
		//No longer stopped
		_stopTime = 0;
		_isRunning = true;
	}
}
void Timer::pause()
{
}
void Timer::resume()
{
}
void Timer::stop()
{
	//If we are already stopped, then don't do anything
	if (!_isRunning) {
		return;
	}
	//Save the time we stopped at
	uint32_t currTime = static_cast<uint32_t>(chronos::now().time_since_epoch() / std::chrono::milliseconds(1));
	_stopTime = currTime;
	// and set the boolean flag indicator the timer stopped
	_isRunning = false;
}

uint32_t Timer::getRunningTime() const
{
	return uint32_t();
}

uint32_t Timer::getPausedTime() const
{
	return uint32_t();
}

float Timer::getDeltaTime() const
{
	return _deltaTime;
}
