#pragma once
#include "Genome.h"
#include "Neat.h"
#include "SynapseSortHelper.h"
#include "MateHelper.h"


class MutableGenome : public Genome {
private:
	IOutputNeuronFactory* factory;
	Phenotype* phenotype;

	void SaveNeurons(std::ostream& file);
protected:
	//std::multimap<Synapse*, int, SynapseCompare> synapseMap;
	std::vector<Synapse*> allTraits;
	MutableGenome();

	virtual void AddSynapseFromTrait(Trait* trait) override;

public:
	MutableGenome(std::istream& file, IOutputNeuronFactory* _factory);
	MutableGenome(Phenotype* _phenotype, int hiddenNum, std::vector<std::string> outputTagVector, std::vector<std::string> inputTagVector, IOutputNeuronFactory* _factory);
	~MutableGenome();

	MutableGenome* Mate(MutableGenome* father);
	void MutateAddNeuron();
	void MutateAddSynapse();

	void SaveGenomeToFile(std::ostream& file);
};

