#pragma once
#include "Neuron.h"

class OutputNeuron : public Neuron {
private:
	std::string tag;
	

protected:
	virtual void reactActivation() = 0;
	virtual void reactNonActivation() = 0;

public:
	OutputNeuron(std::string _tag);
	virtual ~OutputNeuron();

	std::string getTag() const;

	//This is the action that the neuron performs when it is activated.
	void react();

	//This is just for sorting purposes when we decide which neuron to activate.
	bool operator() (Neuron* node1, Neuron* node2) {
		return node1->getTotalInput() > node2->getTotalInput();
	}
};

