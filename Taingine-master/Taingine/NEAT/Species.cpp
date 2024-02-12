#include "stdafx.h"
#include "Species.h"


Species::Species() {
}


Species::~Species() {
	std::vector<Organism*>::iterator curOrganism;
	for (curOrganism = organisms.begin(); curOrganism != organisms.end(); ++curOrganism) {
		delete (*curOrganism);
	}
}
