#include "stdafx.h"
#include "Population.h"


Population::Population() {

}


Population::~Population() {
	if (species.begin() != species.end()) {
		std::vector<Species*>::iterator curspec;
		for (curspec = species.begin(); curspec != species.end(); ++curspec) {
			delete (*curspec);
		}
	}
	else {
		std::vector<Organism*>::iterator curorg;
		for (curorg = organisms.begin(); curorg != organisms.end(); ++curorg) {
			delete (*curorg);
		}
	}
}

void Population::evolve() {

}
