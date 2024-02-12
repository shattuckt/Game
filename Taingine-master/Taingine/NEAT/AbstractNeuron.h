#pragma once
#include "Synapse.h"
#include <vector>

class Synapse;

class AbstractNeuron {
private:
	std::vector<Synapse*> synapses;

public:
	AbstractNeuron();
	virtual ~AbstractNeuron();

	void AddSynapse(Synapse* synapse);
	std::vector<Synapse*> GetSynapseList();

	void Activate(double input);
	virtual void AddInput(double input) = 0;
};

