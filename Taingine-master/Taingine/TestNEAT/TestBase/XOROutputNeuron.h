#pragma once
#include "OutputNeuron.h"
#include "XORActivationReturn.h"

class XOROutputNeuron : public OutputNeuron {
private:
	XORActivationReturn* returnValue;

public:
	XOROutputNeuron(std::string _tag, XORActivationReturn* _returnValue);
	~XOROutputNeuron();

	virtual void reactActivation() override;
	virtual void reactNonActivation() override;
	

	int getExecutedValue();
};

