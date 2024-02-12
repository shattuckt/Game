#include "stdafx.h"
#include "Synapse.h"


Synapse::Synapse(double _weight) {
	weight = _weight;
}


Synapse::Synapse(AbstractNeuron* _targetNeuron, double _weight) {
	targetNeuron = _targetNeuron;
	weight = _weight;
}


void Synapse::sendSignal(double input) {
	targetNeuron->AddInput(weight * input);
}


void Synapse::SetTargetNeuron(AbstractNeuron* _targetNeuron) {
	targetNeuron = _targetNeuron;
}


void Synapse::SetWeight(double _weight) {
	weight = _weight;
}
