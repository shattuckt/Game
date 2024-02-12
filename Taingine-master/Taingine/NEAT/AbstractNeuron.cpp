#include "stdafx.h"
#include "AbstractNeuron.h"


AbstractNeuron::AbstractNeuron() {
}


AbstractNeuron::~AbstractNeuron() {
	std::vector<Synapse*>::iterator curSynapse;;
	for (curSynapse = synapses.begin(); curSynapse != synapses.end(); ++curSynapse) {
		delete (*curSynapse);
	}
}


void AbstractNeuron::AddSynapse(Synapse* synapse) {
	synapses.push_back(synapse);
}


std::vector<Synapse*> AbstractNeuron::GetSynapseList() {
	return synapses;
}


void AbstractNeuron::Activate(double input) {
	std::vector<Synapse*>::iterator synapseIter;
	for (synapseIter = synapses.begin(); synapseIter != synapses.end(); ++synapseIter) {
		(*synapseIter)->sendSignal(input);
	}
}
