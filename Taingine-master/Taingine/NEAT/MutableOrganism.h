#pragma once
#include "Organism.h"
#include "MutableGenome.h"

class MutableOrganism : public Organism {
public:
	MutableOrganism(Genome* _genome);
	MutableOrganism(std::string _fileName);
	~MutableOrganism();

	void mutate();
};

