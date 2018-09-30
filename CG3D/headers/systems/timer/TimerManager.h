#pragma once

namespace cg3d
{
	class Timer;

	class TimerManager
	{
	public:
		static TimerManager& get()
		{
			static TimerManager _instance;
			return _instance;
		}
	private:
		std::map <std::string, Timer*> _timers;
		TimerManager();
	public:
		~TimerManager();
		void update();
		Timer* getTimerByName(std::string name);
		
		bool addTimer(std::string name);
		bool removeTimer(std::string name);
	};
}