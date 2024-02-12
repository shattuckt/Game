#pragma once
#include "Species.h"
#include "Organism.h"

class Population {
private:
	std::vector<Organism *> organisms;
	std::vector<Species *> species;

public:
	Population();
	~Population();

	void evolve();
};

