#pragma once
#include "Trait.h"
#include "FileUtility.h"
#include <vector>

class Phenotype {
private:
	std::vector<Trait*> traits;
	std::vector<Trait*> activeTraits;

public:
	Phenotype(std::istream& file, u32 numberOfTraits);
	Phenotype(std::vector<Trait*> _traits);
	~Phenotype();

	std::vector<Trait*> GetTraits();
	std::vector<Trait*>::iterator getTraitIterStart();
	std::vector<Trait*>::iterator getTraitIterEnd();
	std::vector<Trait*>::iterator GetActiveTraitIterStart();
	std::vector<Trait*>::iterator GetActiveTraitIterEnd();

	int GetNumActiveTraits() const;
	Trait* GetActiveTraitAt(int index);
	void AddTrait(Trait* trait);

	void SavePhenotypeToFile(std::ostream& file);
};

