#include "stdafx.h"
#include "Neuron.h"


Neuron::Neuron() {
	numDependencies = 0;
	defauntNumDependencies = 0;
}


Neuron::~Neuron() {
}


void Neuron::resetNeuron() {
	//Go back to number of dependencies and totalInput when no neurons have been activated.
	numDependencies = defauntNumDependencies;
	totalInput = 0;
}

void Neuron::AddInput(double input) {
	numDependencies--;
	totalInput += input;

	//If all the nodes we are dependend on activate and we have a high enouph input activate other nodes.
	if (numDependencies < 1 && totalInput >= THRESHOLD) {
		Activate(totalInput);
		activationCount++;
	}
}


void Neuron::increaseDependency() {
	defauntNumDependencies++;
	numDependencies++;
}


int Neuron::getTotalInput() const {
	return totalInput;
}


bool Neuron::shouldActivate() {
	return totalInput >= THRESHOLD;
}


int Neuron::getDefaultNumberOfDependencies() const {
	return defauntNumDependencies;
}

