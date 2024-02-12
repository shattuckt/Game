#pragma once
#include "stdafx.h"
#include "Trait.h"
#include "SynapseSortHelper.h"
#include <map>

namespace NEAT {
	extern int innovationNumber;
	extern std::multimap<Trait*, int, TraitCompare> innovations;

	extern int getInnovationNum(Trait* _Trait);
	extern void ResetGenerationMap();
}