#pragma once
#include "Synapse.h"

class Trait : public Synapse {
private:
	bool isDisabled;
	int start;
	int target;
	//double weight;
	int innovationNumber;
	//Synapse* networkRepresentation;

public:
	Trait(int _start, int _target, double _weight, int _innovationNumber);
	Trait(int _start, int _target, double _weight, int _innovationNumber, bool _isDisabled);
	~Trait();

	int getStart() const;
	int getTarget() const;
	double getWeight() const;
	bool getIsDisabled() const;
	int getInnovationNumber() const;


	//Synapse* getNetworkRepresentation();
	void setNetworkRepresentation(Synapse* synapse);
	void SetIsDisabled(bool _isDisabled);
};

