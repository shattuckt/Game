#include "stdafx.h"
#include "OutputNeuron.h"


OutputNeuron::OutputNeuron(std::string _tag)
	: Neuron() {
	tag = _tag;
}


OutputNeuron::~OutputNeuron() {
}


std::string OutputNeuron::getTag() const {
	return tag;
}


void OutputNeuron::react() {
	getTotalInput() > 0 ? reactActivation() : reactNonActivation();
}