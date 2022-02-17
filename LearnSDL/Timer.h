#pragma once
#include <SDL.h>
class Timer
{
private:
	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

public:
	static Timer* Instance();
	static void Release();

	void Reset();

	float DeltaTime();
	void TimeScale(float t); // setting the time scale
	float TimeScale();

	void Update(); // update for timer

private:

	Timer();
	~Timer();

};
