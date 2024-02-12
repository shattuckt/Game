#include "stdafx.h"
#include "Organism.h"


Organism::Organism() {

}


Organism::Organism(Genome* _genome) {

}


Organism::Organism(std::string _fileName) {
	//genome = new Genome(_fileName);
}


Organism::~Organism() {
	delete genome;
}


int Organism::getAge() const {
	return age;
}

void Organism::incramentAge() {
	age++;
}

double Organism::getFitness() const {
	return fitness;
}
