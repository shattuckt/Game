#pragma once
#include "AbstractNeuron.h"
#include <string>

class AbstractNeuron;

class Synapse {
protected:
	AbstractNeuron* targetNeuron;
	double weight;

	Synapse(double _weight);

public:
	Synapse(AbstractNeuron* _targetNeuron, double _weight);
	void sendSignal(double input);

	void SetTargetNeuron(AbstractNeuron* _targetNeuron);
	void SetWeight(double _weight);
};

