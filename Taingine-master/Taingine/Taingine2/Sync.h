#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Sync{
private:
	class RunningAvg {
	private:
		std::vector<double> slots;
		int slotCount;
		int offset;

		static double DAMPEN_THRESHOLD;
		static float DAMPEN_FACTOR;

	public:
		RunningAvg(int slotCount);
		void init(double value);
		void add(double value);
		double avg();
		void dampenForLowResTicker();
	};

	static double NANOS_IN_SECOND;
	double nextFrame = 0;
	bool initialized = false;
    RunningAvg* sleepDurations = new RunningAvg(10);
	RunningAvg* yieldDurations = new RunningAvg(10);
	int fps;

	void initialise();
	double getTime();

public:
	Sync(int fps);
	int getFps();
	void setFps(int fps);
	void sync();



};

