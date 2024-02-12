#pragma once
#include "AbstractNeuron.h"

class InputNeuron : public AbstractNeuron {
private:
	std::string tag;

public:
	InputNeuron(std::string _tag);
	~InputNeuron();

	std::string GetTag() const;

	virtual void AddInput(double input) override;
};

