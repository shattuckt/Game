#pragma once
#include "AbstractNeuron.h"
#include <string>

//class AbstractNeuron;

class Neuron : public AbstractNeuron {
private:
	//The threshold needed to activate the neuron.
	const double THRESHOLD = 1;

	//The number of neurons that need to activate before this one can.
	int defauntNumDependencies;
	int numDependencies;

	//How active the neuron is.
	int activationCount = 0;

	//How close we are to the threshold.
	double totalInput = 0;

public:
	Neuron();
	virtual ~Neuron();

	//Resets the totalInput and Depedency numbers.  
	//We do this so that the same network can be activated again from a clean slate, 
	//so that previouse activations don't affect current ones.
	void resetNeuron();

	//Another neuron has send a singnal to this adding to its totalInput.
	//If the total input is great enouph we to sent inputs to other nodes.
	virtual void AddInput(double input) override;

	//Setters
	void increaseDependency();

	//Getters
	int getTotalInput() const;
	bool shouldActivate();
	int getDefaultNumberOfDependencies() const;
};
