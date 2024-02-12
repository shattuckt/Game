#include "Timer.h"

float Timer::MAX_DELTA = 0.1f;
float Timer::STABLE_TIME = 1.5f;
int Timer::ROLL_AVG_COUNT = 20;

int Timer::NANOS_IN_SECOND = 1000 * 1000 * 1000;

Timer::Timer(int idealFps) {
	this->idealDelta = 1.0f / idealFps;
	this->delta = idealDelta;
	this->lastFrameTime = getCurrentTime();
}

void Timer::update() {
	double currentFrameTime = getCurrentTime();
	float frameLength = std::min(MAX_DELTA, (float)(currentFrameTime - lastFrameTime) / NANOS_IN_SECOND);
	this->lastFrameTime = currentFrameTime;
	applicationTime += frameLength;
	if (applicationTime < STABLE_TIME) {
		frameLength = idealDelta;
	}
	deltaAverage->addValue(frameLength);
	this->delta = deltaAverage->getAverage();
}
float Timer::getDelta() {
	return delta;
}
double Timer::getCurrentTime() {
	return glfwGetTime() * NANOS_IN_SECOND;
}