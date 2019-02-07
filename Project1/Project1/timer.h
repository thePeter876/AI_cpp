#pragma once
#include <time.h>
#include <chrono>
class Timer
{
private:
	std::chrono::steady_clock::time_point startMoment;
	__int64 currentCount;
	bool counting;

public:
	Timer() {
		startMoment = std::chrono::steady_clock::now();
		counting = true;
	}

	inline void start() {
		startMoment = std::chrono::steady_clock::now();
		counting = true;
	}

	inline __int64 stop() {
		counting = false;
		currentCount = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::steady_clock::now() - std::chrono::steady_clock::time_point(startMoment)).count();
		return currentCount;
	}

	inline __int64 getTimeElapsed() {
		currentCount = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::steady_clock::now() - std::chrono::steady_clock::time_point(startMoment)).count();
		return currentCount;
	}
	~Timer() {}
};