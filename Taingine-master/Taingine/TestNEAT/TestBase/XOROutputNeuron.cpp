#include "..\pch.h"
#include "XOROutputNeuron.h"


XOROutputNeuron::XOROutputNeuron(std::string _tag, XORActivationReturn* _returnValue) : OutputNeuron(_tag) {
	returnValue = _returnValue;
}


XOROutputNeuron::~XOROutputNeuron() {
	//delete returnValue;
}


void XOROutputNeuron::reactActivation() {
	returnValue->setValue(1);
}


void XOROutputNeuron::reactNonActivation() {
	returnValue->setValue(0);
}


int XOROutputNeuron::getExecutedValue() {
	return returnValue->getValue();
}