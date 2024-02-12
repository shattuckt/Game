#pragma once
#include "Organism.h"
#include <vector>

class Organism;

class Species {
private:
	std::vector<Organism*> organisms;

public:
	Species();
	~Species();
};

