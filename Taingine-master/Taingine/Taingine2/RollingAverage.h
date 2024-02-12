#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RollingAverage{
private:

	unsigned int max;
	unsigned int count = 0;

	double *values;
	double sum = 0;
	double average;

public:
	RollingAverage(int count);

	void addValue(double value);
	double getAverage();

};

