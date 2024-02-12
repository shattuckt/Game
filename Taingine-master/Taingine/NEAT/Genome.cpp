#include "stdafx.h"
#include "Genome.h"
#include <io.h>


Genome::Genome(std::istream& file, IOutputNeuronFactory* factory) {
	LoadNeurons(file, factory);
	Phenotype* phenotype = loadPhenotype(file);
	constructGonomeFromPhenotype(phenotype);

	delete phenotype;
}


Genome::Genome() {

}

Genome::~Genome() {
	std::vector<AbstractNeuron*>::iterator curNeuron;
	for (curNeuron = allNeurons.begin(); curNeuron != allNeurons.end(); ++curNeuron) {
		delete (*curNeuron);//Have to make sure to delete all the neuron pointers as we dynamically create them with new.
	}
}


#pragma region Load Genome

void Genome::LoadNeurons(std::istream& file, IOutputNeuronFactory* factory) {
	u32 numberOfInputNeurons = FileUtility::readUnsignedInt(file);
	for (u32 i = 0; i < numberOfInputNeurons; i++) {
		std::string tag = FileUtility::readString(file);
		InputNeuron* node = new InputNeuron(tag);
		inputNeurons.push_back(node);
		allNeurons.push_back(node);
	}

	u32 numberOfOutputNeurons = FileUtility::readUnsignedInt(file);
	for (u32 i = 0; i < numberOfOutputNeurons; i++) {
		std::string tag = FileUtility::readString(file);
		OutputNeuron* node = factory->create(tag);
		outputNeurons.push_back(node);
		allNeurons.push_back(node);
	}

	u32 numberOfHiddenNeurons = FileUtility::readUnsignedInt(file);
	for (u32 i = 0; i < numberOfHiddenNeurons; i++) {
		Neuron* node = new Neuron();
		allNeurons.push_back(node);
	}
}


Phenotype* Genome::loadPhenotype(std::istream& file) {
	u32 numberOfTraits = FileUtility::readUnsignedInt(file);
	Phenotype* phenotype = new Phenotype(file, numberOfTraits);
	return phenotype;
}


void Genome::constructGonomeFromPhenotype(Phenotype* phenotype) {
	std::vector<Trait*>::iterator traitIter;
	for (traitIter = phenotype->GetActiveTraitIterStart(); traitIter != phenotype->GetActiveTraitIterEnd(); ++traitIter) {
		AddSynapseFromTrait((*traitIter));
	}
}


void Genome::AddSynapseFromTrait(Trait* trait) {
	Neuron* targetNeuron = (Neuron*)allNeurons.at(trait->getTarget());
	targetNeuron->increaseDependency();
	Synapse* synapse = new Synapse(targetNeuron, trait->getWeight());

	AbstractNeuron* startNeuron = allNeurons.at(trait->getStart());
	startNeuron->AddSynapse(synapse);
}

#pragma endregion 


void Genome::execute(std::map<std::string, double> input) {
	std::map<std::string, double>::iterator mapIter;
	std::vector<InputNeuron*>::iterator neuronIter;
	for (neuronIter = inputNeurons.begin(); neuronIter != inputNeurons.end(); ++neuronIter) {
		std::string tag = (*neuronIter)->GetTag();
		mapIter = input.find(tag);
		if (mapIter != input.end()) {
			(*neuronIter)->AddInput((*mapIter).second);
		}
		else {
			//TODO tell user thath they passed the wrong map: give them tag
		}
	}

	//We find the highest activation amoung all OutputNeurons and activate that neuron.
	OutputNeuron* highestOutNeuron = outputNeurons.front();
	std::vector<OutputNeuron*>::iterator outNeuronIter;
	for (outNeuronIter = outputNeurons.begin(); outNeuronIter != outputNeurons.end(); ++outNeuronIter) {
		if ((*outNeuronIter)->getTotalInput() > highestOutNeuron->getTotalInput())
			highestOutNeuron = (*outNeuronIter);
	}


	highestOutNeuron->react();
}


int Genome::getFitness() const {
	return fitness;
}


void Genome::calculateFitness() {
	//TODO:-
}


void Genome::resetNeurons() {
	std::vector<AbstractNeuron*>::iterator nodeIter;
	for (nodeIter = allNeurons.begin() + inputNeurons.size(); nodeIter != allNeurons.end(); ++nodeIter) {
		((Neuron*)(*nodeIter))->resetNeuron();
	}
}
