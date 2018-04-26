#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <string>
#define UNLIMITED -1.0
using namespace std::chrono;
class Timer
{
public:
	Timer() { m_count = 60; m_start  = high_resolution_clock::now(); }
	~Timer() {}
	void setUpdateCount(double count) { this->m_count = count; }
	void startTimer() { this->m_start = high_resolution_clock::now(); }
	bool update()
	{
		if (m_count == UNLIMITED)
			return true;
		high_resolution_clock::time_point current = high_resolution_clock::now();
		duration<double, std::milli> deltaTime = current - m_start;
		if (deltaTime.count() >= (1.0 / m_count) * 1000.0)
		{
			//OutputDebugString((std::to_wstring(deltaTime.count()) + L"\n").c_str());
			m_start = current;
			return true;
		}
		return false;
	}

	bool checkDT(float to_wait)
	{
		high_resolution_clock::time_point current = high_resolution_clock::now();
		timer += current - m_start;
		if (to_wait < timer.count())
		{
			timer.zero();
			return true;
		}
		return false;
	}

private:
	std::chrono::high_resolution_clock::time_point m_start;
	double m_count;
	duration<double, std::milli> timer;
};
#endif //TIMER_H

