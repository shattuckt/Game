#include "RollingAverage.h"



RollingAverage::RollingAverage(int count) {
	this->max = count;
	this->values = new double[this->max];
}

void RollingAverage::addValue(double value) {
	sum -= values[count];
	sum += value;
	values[count] = value;
	if (count >= max) {
		count = 0;
	}
	else {
		count++;
	}
	this->average = sum / max;
}

double RollingAverage::getAverage() {
	return this->average;
}
