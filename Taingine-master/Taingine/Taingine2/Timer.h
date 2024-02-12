#pragma once
#include "RollingAverage.h"
#include <algorithm>

class Timer{

private:
	static float MAX_DELTA;
	static float STABLE_TIME;
	static int ROLL_AVG_COUNT;

	static int NANOS_IN_SECOND;

	float idealDelta;

	RollingAverage* deltaAverage = new RollingAverage(ROLL_AVG_COUNT);

	double lastFrameTime;
	float applicationTime = 0;
	float delta;

public:
	Timer(int idealFps);
	void update();
	float getDelta();
	double getCurrentTime();
};

