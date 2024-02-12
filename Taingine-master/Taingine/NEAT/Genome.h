#pragma once
#include "FileUtility.h"
#include "Utility.h"
#include "Neuron.h"
#include "OutputNeuron.h"
#include "InputNeuron.h"
#include "IOutputNeuronFactory.h"
#include "Phenotype.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <map>

class Genome {
private:
	double fitness;	

protected:
	std::vector<InputNeuron*> inputNeurons;
	std::vector<OutputNeuron*> outputNeurons;
	std::vector<AbstractNeuron*> allNeurons;

	void LoadNeurons(std::istream& file, IOutputNeuronFactory* factory);
	Phenotype* loadPhenotype(std::istream& file);
	void constructGonomeFromPhenotype(Phenotype* phenotype);
	virtual void AddSynapseFromTrait(Trait* trait);

	Genome();
	//Genome(std::istream& file, IOutputNeuronFactory* factory);
	//Genome(Phenotype* phenotype, std::string _path, IOutputNeuronFactory* factory);

public:
	Genome(std::istream& file, IOutputNeuronFactory* factory);
	~Genome();

	//Executes the network.  Inputs is a list of initial values for the input neurons.
	void execute(std::map<std::string, double> input);

	int getFitness() const;

	void calculateFitness();

	//Reset internal values in the Neurons so that the network can be activated again from a neutral position.
	void resetNeurons();
};

