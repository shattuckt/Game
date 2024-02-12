#include "stdafx.h"
#include "Trait.h"


Trait::Trait(int _start, int _target, double _weight, int _innovationNumber) : 
	Trait(_start, _target, _weight, _innovationNumber, false){
}


Trait::Trait(int _start, int _target, double _weight, int _innovationNumber, bool _isDisabled) : Synapse(_weight) {
	start = _start;
	target = _target;
	//weight = _weight;
	innovationNumber = _innovationNumber;
	isDisabled = _isDisabled;
	//networkRepresentation = nullptr;
}


Trait::~Trait() {

}


int Trait::getStart() const {
	return start;
}


int Trait::getTarget() const {
	return target;
}


double Trait::getWeight() const {
	return weight;
}


bool Trait::getIsDisabled() const {
	return isDisabled;
}


int Trait::getInnovationNumber() const {
	return innovationNumber;
}


//Synapse* Trait::getNetworkRepresentation() {
//	return networkRepresentation;
//}


//void Trait::setNetworkRepresentation(Synapse* synapse) {
//	networkRepresentation = synapse;
//}


void Trait::SetIsDisabled(bool _isDisabled) {
	isDisabled = _isDisabled;
}
