#pragma once
#include "Genome.h"
#include "Species.h"

class Species;

class Organism {
private:
	Species *species;
	int age;
	double fitness;

protected:
	Genome * genome;
	Organism();

public:
	Organism(Genome* _genome);
	Organism(std::string _fileName);
	~Organism();

	int getAge() const;
	void incramentAge();
	double getFitness() const;
};

