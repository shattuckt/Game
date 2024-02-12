#pragma once
#include "Trait.h"

struct TraitInovSort {
	bool operator() (const Trait* lhs, const Trait* rhs) {
		return lhs->getInnovationNumber() < rhs->getInnovationNumber();
	}
};

const struct TraitCompare {
	bool operator() (const Trait* lhs, const Trait* rhs) const {
		int lhsxor = lhs->getStart() ^ lhs->getTarget();
		int rhsxor = rhs->getStart() ^ rhs->getTarget();
		if (lhsxor == rhsxor && lhs->getStart() == rhs->getTarget()) {
			return lhs->getStart() < rhs->getStart();
		}
		return lhsxor < rhsxor;
	}
};