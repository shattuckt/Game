#include "stdafx.h"
#include "MutableGenome.h"


#pragma region Constructor

MutableGenome::MutableGenome(std::istream& file, IOutputNeuronFactory* _factory) {
	//std::ifstream file(_path);
	factory = _factory;

	LoadNeurons(file, factory);
	phenotype = loadPhenotype(file);
	constructGonomeFromPhenotype(phenotype);

	//file.close();
}


MutableGenome::MutableGenome(Phenotype* _phenotype, int hiddenNum, std::vector<std::string> outputTagVector, std::vector<std::string> inputTagVector, IOutputNeuronFactory* _factory) {
	factory = _factory;
	phenotype = _phenotype;

	std::vector<std::string>::iterator inputTagIter;
	for (inputTagIter = inputTagVector.begin(); inputTagIter != inputTagVector.end(); ++inputTagIter) {
		InputNeuron* inputNeuron = new InputNeuron((*inputTagIter));
		allNeurons.push_back(inputNeuron);
		inputNeurons.push_back(inputNeuron);
	}

	std::vector<std::string>::iterator outputTagIter;
	for (outputTagIter = outputTagVector.begin(); outputTagIter != outputTagVector.end(); ++outputTagIter) {
		OutputNeuron* outputNeuron = factory->create((*outputTagIter));
		allNeurons.push_back(outputNeuron);
		outputNeurons.push_back(outputNeuron);
	}

	for (int i = 0; i < hiddenNum; i++) {
		Neuron* inputNeuron = new Neuron();
		allNeurons.push_back(inputNeuron);
	}

	constructGonomeFromPhenotype(phenotype);
}

#pragma endregion


MutableGenome::~MutableGenome() {
	delete phenotype;
}

void MutableGenome::AddSynapseFromTrait(Trait* trait) {
	Neuron* targetNeuron = (Neuron*)allNeurons.at(trait->getTarget());
	targetNeuron->increaseDependency();
	trait->SetTargetNeuron(targetNeuron);

	AbstractNeuron* startNeuron = allNeurons.at(trait->getStart());
	startNeuron->AddSynapse(trait);
}

#pragma region Save Genome

void MutableGenome::SaveGenomeToFile(std::ostream& file) {
	SaveNeurons(file);
	phenotype->SavePhenotypeToFile(file);
}


void MutableGenome::SaveNeurons(std::ostream& file) {
	FileUtility::writeUnsignedInt(file, inputNeurons.size());
	std::vector<InputNeuron*>::iterator inputIter;
	for (inputIter = inputNeurons.begin(); inputIter != inputNeurons.end(); ++inputIter) {
		FileUtility::writeString(file, (*inputIter)->GetTag());
	}

	FileUtility::writeUnsignedInt(file, outputNeurons.size());
	std::vector<OutputNeuron*>::iterator outputIter;
	for (outputIter = outputNeurons.begin(); outputIter != outputNeurons.end(); ++outputIter) {
		FileUtility::writeString(file, (*outputIter)->getTag());
	}

	FileUtility::writeUnsignedInt(file, allNeurons.size() - (inputNeurons.size() + outputNeurons.size()));
}

#pragma endregion

#pragma region Genetic Mutations

MutableGenome* MutableGenome::Mate(MutableGenome* father) {
	int ioSize = inputNeurons.size() + outputNeurons.size();
	MateHelper helper = MateHelper(ioSize);
	
	std::vector<Trait*> childTraits;

	std::vector<Trait*> motherTraits = phenotype->GetTraits();
	std::vector<Trait*> fatherTraits = father->phenotype->GetTraits();

	size_t motherIndex = 0;
	size_t fatherIndex = 0;

	Trait* motherTrait = motherTraits[0];
	Trait* fatherTrait = fatherTraits[0];
	int motherInnovationNumber = motherTrait->getInnovationNumber();
	int fatherInnovationNumber = fatherTrait->getInnovationNumber();

	while (motherTrait != nullptr
		|| fatherTrait != nullptr) {

		if (motherInnovationNumber == fatherInnovationNumber) {
			int start = helper.getBlendedMap(motherTrait->getStart(), fatherTrait->getStart());
			int target = helper.getBlendedMap(motherTrait->getTarget(), fatherTrait->getTarget());
			double weight = motherTrait->getWeight();

			if (motherTrait->getIsDisabled() || fatherTrait->getIsDisabled()) {
				Trait* trait = new Trait(start, target, 1, motherInnovationNumber, true);
				childTraits.push_back(trait);
			}
			else {
				Trait* trait = new Trait(start, target, weight, motherInnovationNumber, false);
				childTraits.push_back(trait);
			}

			++motherIndex;
			++fatherIndex;
		}
		else if (motherInnovationNumber < fatherInnovationNumber) {
			int start = helper.getMotherMap(motherTrait->getStart());
			int target = helper.getMotherMap(motherTrait->getTarget());
			double weight = motherTrait->getWeight();
			bool isDisabled = motherTrait->getIsDisabled();

			Trait* trait = new Trait(start, target, weight, motherInnovationNumber, isDisabled);
			childTraits.push_back(trait);
			++motherIndex;
		}
		else {
			int start = helper.getFatherMap(fatherTrait->getStart());
			int target = helper.getFatherMap(fatherTrait->getTarget());
			double weight = fatherTrait->getWeight();
			bool isDisabled = fatherTrait->getIsDisabled();

			Trait* trait = new Trait(start, target, weight, fatherInnovationNumber, isDisabled);
			childTraits.push_back(trait);
			++fatherIndex;
		}

		if (motherIndex < motherTraits.size()) {
			motherTrait = motherTraits[motherIndex];
			motherInnovationNumber = motherTrait->getInnovationNumber();
		}
		else {
			motherTrait = nullptr;
			motherInnovationNumber = INT_MAX;
		}
		if (fatherIndex < fatherTraits.size()) {
			fatherTrait = fatherTraits[fatherIndex];
			fatherInnovationNumber = fatherTrait->getInnovationNumber();
		}
		else {
			fatherTrait = nullptr;
			fatherInnovationNumber = INT_MAX;
		}
	}//end While

	Phenotype* newPhenotype = new Phenotype(childTraits);
	int hiddenNumber = helper.GetChildSize() - (inputNeurons.size() + outputNeurons.size() - 1);
	std::vector<std::string> outputTags;
	std::vector<OutputNeuron*>::iterator outputIter;
	for (outputIter = outputNeurons.begin(); outputIter != outputNeurons.end(); ++outputIter) {
		outputTags.push_back((*outputIter)->getTag());
	}

	std::vector<std::string> inputTags;
	std::vector<InputNeuron*>::iterator inputIter;
	for (inputIter = inputNeurons.begin(); inputIter != inputNeurons.end(); ++inputIter) {
		inputTags.push_back((*inputIter)->GetTag());
	}

	return new MutableGenome(newPhenotype, hiddenNumber, outputTags, inputTags, factory);
}


void MutableGenome::MutateAddNeuron() {
	int min = 0;
	int max = phenotype->GetNumActiveTraits() - 1;
	int index = Utility::RandInt(min, max);
	Trait* oldTrait = phenotype->GetActiveTraitAt(index);
	oldTrait->SetIsDisabled(true);

	Trait* firstTrait = new Trait(oldTrait->getStart(), allNeurons.size(), 1, 1);//TODO innovationNumber thing
	Trait* secondTrait = new Trait(allNeurons.size(), oldTrait->getTarget(), oldTrait->getWeight(), 1);
	phenotype->AddTrait(firstTrait);
	phenotype->AddTrait(secondTrait);

	Neuron* newNeuron = new Neuron();
	allNeurons.push_back(newNeuron);

	oldTrait->SetTargetNeuron(newNeuron);
	oldTrait->SetWeight(1);

	AddSynapseFromTrait(secondTrait);
}


void MutableGenome::MutateAddSynapse() {

	int tries = 1;
	int randStartIndex;
	AbstractNeuron* randStartNeuron;

	do {
		randStartIndex = Utility::RandInt(0, allNeurons.size() - outputNeurons.size());

		randStartNeuron = randStartIndex >= inputNeurons.size() ?
			allNeurons.at(randStartIndex + outputNeurons.size() - 1) :
			inputNeurons.at(randStartIndex);
		
	} while (randStartNeuron->GetSynapseList().size() == (allNeurons.size() - 1) && tries++ < allNeurons.size());

	std::vector<Synapse*> list = randStartNeuron->GetSynapseList();
	//std::vector<Trait*> list(list1.begin(), list1.end());
	int randTargetIndex = Utility::RandInt(0, allNeurons.size() - inputNeurons.size() - list.size() - 1);

	int maxNeuronMun = allNeurons.size() - inputNeurons.size() - 1;
	int uniqe = 0;
	for (int i = 0; i < list.size(); i++) {
		Trait* trait = static_cast<Trait*>(list.at(i));
		if (i != trait->getTarget()) {
			uniqe++;
			if (uniqe == randTargetIndex) {
				randTargetIndex = i + inputNeurons.size();
				break;
			}
		}
	}


	Neuron* randTragetNeuron = (Neuron*)allNeurons.at(randTargetIndex);
	randTragetNeuron->increaseDependency();
	Trait* newTrait = new Trait(randStartIndex, randTargetIndex, 0, 1);
	allTraits.push_back(newTrait);
	randStartNeuron->AddSynapse(newTrait);
}

#pragma endregion

