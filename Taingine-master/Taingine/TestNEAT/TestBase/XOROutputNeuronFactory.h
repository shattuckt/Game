#pragma once
#include "IOutputNeuronFactory.h"
#include "XOROutputNeuron.h"
#include "XORActivationReturn.h"

class XOROutputNeuronFactory : public IOutputNeuronFactory {
private:
	XORActivationReturn* returnValue;

public:
	XOROutputNeuronFactory(XORActivationReturn* _returnValue);
	~XOROutputNeuronFactory();

	virtual OutputNeuron* create(std::string _tag) override;
	//virtual OutputNeuron* create(OutputNeuron* seed) override;
};

