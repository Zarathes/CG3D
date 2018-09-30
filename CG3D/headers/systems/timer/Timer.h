#pragma once

namespace cg3d
{
	class Timer
	{
	private:
		bool _isRunning;
		std::string _name;
		
		float _deltaTime;

		uint32_t _baseTime;
		uint32_t _pauseTime;
		uint32_t _stopTime;
		uint32_t _prevTime;
	public:
		Timer(std::string name);
		~Timer();
		

		void update();
		void start();
		void pause();
		void resume();
		void stop();

		uint32_t getRunningTime() const;
		uint32_t getPausedTime() const;
		float getDeltaTime() const;
	};
}