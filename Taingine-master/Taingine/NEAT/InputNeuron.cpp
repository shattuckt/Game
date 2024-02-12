#include "stdafx.h"
#include "InputNeuron.h"


InputNeuron::InputNeuron(std::string _tag) {
	tag = _tag;
}


InputNeuron::~InputNeuron() {
}


std::string InputNeuron::GetTag() const {
	return tag;
}

void InputNeuron::AddInput(double input) {
	Activate(input);
}
