#include "..\pch.h"
#include "XOROutputNeuronFactory.h"


XOROutputNeuronFactory::XOROutputNeuronFactory(XORActivationReturn* _returnValue)
{
	returnValue = _returnValue;
}


XOROutputNeuronFactory::~XOROutputNeuronFactory()
{
	//delete value;
}

OutputNeuron* XOROutputNeuronFactory::create(std::string _tag) {
	return new XOROutputNeuron(_tag, returnValue);
}

//OutputNeuron* XOROutputNeuronFactory::create(OutputNeuron* seed) {
//	int dependencies = seed->getDefaultNumberOfDependencies();
//	int id = seed->getId();
//	return new XOROutputNeuron(dependencies, id, returnValue);
//}
