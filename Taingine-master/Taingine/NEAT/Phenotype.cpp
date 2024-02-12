#include "stdafx.h"
#include "Phenotype.h"


Phenotype::Phenotype(std::istream& file, u32 numberOfTraits) {
	traits.reserve(numberOfTraits);
	for (int i = 0; i < numberOfTraits; i++) {
		int start = FileUtility::readInt(file);
		int target = FileUtility::readInt(file);
		double weight = FileUtility::readDouble(file);
		int innovationNumber = FileUtility::readInt(file);
		bool isDisabled = FileUtility::readByte(file);

		Trait* trait = new Trait(start, target, weight, innovationNumber, isDisabled);
		traits.push_back(trait);
		if (!isDisabled) 
			activeTraits.push_back(trait);
	}
}

Phenotype::Phenotype(std::vector<Trait*> _traits) {
	traits = _traits;
	std::vector<Trait*>::iterator curTrait;
	for (curTrait = traits.begin(); curTrait != traits.end(); ++curTrait) {
		if (!(*curTrait)->getIsDisabled())
			activeTraits.push_back((*curTrait));
	}
}


Phenotype::~Phenotype() {
	//std::vector<Trait*>::iterator curTrait;
	//for (curTrait = traits.begin(); curTrait != traits.end(); ++curTrait) {
	//	delete (*curTrait);//Have to make sure to delete all the neuron pointers as we dynamically create them with new.
	//}
}


std::vector<Trait*> Phenotype::GetTraits() {
	return traits;
}


std::vector<Trait*>::iterator Phenotype::getTraitIterStart() {
	return traits.begin();
}


std::vector<Trait*>::iterator Phenotype::getTraitIterEnd() {
	return traits.end();
}


std::vector<Trait*>::iterator Phenotype::GetActiveTraitIterStart() {
	return activeTraits.begin();
}


std::vector<Trait*>::iterator Phenotype::GetActiveTraitIterEnd() {
	return activeTraits.end();
}


int Phenotype::GetNumActiveTraits() const {
	return activeTraits.size();
}


Trait* Phenotype::GetActiveTraitAt(int index) {
	return traits.at(index);
}


void Phenotype::AddTrait(Trait* trait) {
	traits.push_back(trait);
}


void Phenotype::SavePhenotypeToFile(std::ostream& file) {
	int size = traits.size();
	FileUtility::writeUnsignedInt(file, size);

	std::vector<Trait*>::iterator traitIter;
	for (traitIter = traits.begin(); traitIter != traits.end(); ++traitIter) {
		FileUtility::writeInt(file, (*traitIter)->getStart());
		FileUtility::writeInt(file, (*traitIter)->getTarget());
		FileUtility::writeDouble(file, (*traitIter)->getWeight());
		FileUtility::writeInt(file, (*traitIter)->getInnovationNumber());
		FileUtility::writeByte(file, (*traitIter)->getIsDisabled());
	}
}