#include "Sync.h"


double Sync::NANOS_IN_SECOND = 1000 * 1000 * 1000;
double Sync::RunningAvg::DAMPEN_THRESHOLD = 10 * 1000 * 1000; // 10 ms
float Sync::RunningAvg::DAMPEN_FACTOR = 0.9f;


Sync::RunningAvg::RunningAvg(int slotCount) {
	this->offset = 0;
	this->slotCount = slotCount;
}

void Sync::RunningAvg::init(double value) {
	for (int x = 0; x < this->slotCount; x++) {
		this->slots.push_back(value);
	}
}

void Sync::RunningAvg::add(double value) {
	this->slots[this->offset++ % this->slots.size()] = value;
	this->offset %= this->slots.size();
}

double Sync::RunningAvg::avg() {
	double sum = 0;
	for (int i = 0; i < this->slots.size(); i++) {
		sum += this->slots[i];
	}
	return sum / this->slots.size();
}

void Sync::RunningAvg::dampenForLowResTicker() {
	if (this->avg() > DAMPEN_THRESHOLD) {
		for (int i = 0; i < this->slots.size(); i++) {
			this->slots[i] *= DAMPEN_FACTOR;
		}
	}
}

Sync::Sync(int fps) {
	this->fps = fps;
}

int Sync::getFps() {
	return fps;
}

void Sync::setFps(int fps) {
	this->fps = fps;
}

void Sync::sync() {
	if (fps <= 0) {
		return;
	}
	if (!initialized) {
		initialise();
	}

	try {
		for (double t0 = getTime(), t1; (nextFrame - t0) > sleepDurations->avg(); t0 = t1) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			sleepDurations->add((t1 = getTime()) - t0); //update average
		}
		sleepDurations->dampenForLowResTicker();

		for (double t0 = getTime(), t1; (nextFrame - t0) > yieldDurations->avg(); t0 = t1) {
			std::this_thread::yield();
			yieldDurations->add((t1 = getTime()) - t0);
		}
	}
	catch (const std::exception & e) {
		std::cout << e.what();
	}
	nextFrame = std::max(nextFrame + NANOS_IN_SECOND / fps, getTime());
}

void Sync::initialise() {
	this->initialized = true;

	sleepDurations->init(1000 * 1000);
	yieldDurations->init((int)(-(getTime() - getTime()) * 1.333));

	nextFrame = getTime();
}

double  Sync::getTime() {
	return glfwGetTime() * NANOS_IN_SECOND;
}