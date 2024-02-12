#include "stdafx.h"
#include "Neat.h"

int NEAT::innovationNumber = 0;
std::multimap<Trait*, int, TraitCompare> NEAT::innovations;

int NEAT::getInnovationNum(Trait* _Trait) {
	if (innovations.find(_Trait) == innovations.end()) {
		innovations.insert(std::make_pair(_Trait, ++innovationNumber));
		return innovationNumber;
	}
	else {
		return innovations.find(_Trait)->second;
	}
}

void NEAT::ResetGenerationMap() {
	innovations.clear();
}