#pragma once
#include "OutputNeuron.h"

class IOutputNeuronFactory {
public:
	virtual ~IOutputNeuronFactory() {}
	virtual OutputNeuron* create(std::string _tag) = 0;
	OutputNeuron* create(OutputNeuron* seed) {
		return create(seed->getTag());
	}
};

//inline IOutputNeuronFactory::~IOutputNeuronFactory() {}