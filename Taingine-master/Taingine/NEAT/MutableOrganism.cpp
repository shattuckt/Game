#include "stdafx.h"
#include "MutableOrganism.h"


MutableOrganism::MutableOrganism(Genome* _genome) : Organism(_genome) {

}


MutableOrganism::MutableOrganism(std::string _fileName) : Organism() {
	//genome = new MutableGenome(_fileName);
}


MutableOrganism::~MutableOrganism()
{
}


void MutableOrganism::mutate() {

}
