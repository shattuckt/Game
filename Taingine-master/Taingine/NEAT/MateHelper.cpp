#include "stdafx.h"
#include "MateHelper.h"


MateHelper::MateHelper(int ioSize) {
	childSize = ioSize - 1;

	for (int i = 0; i < ioSize; i++) {
		motherMap.push_back(i);
		fatherMap.push_back(i);
	}
}


MateHelper::~MateHelper() {
}


int MateHelper::getMotherMap(int index) {
	if (index > motherMap.size()) {
		motherMap.push_back(++childSize);
	}

	return motherMap.at(index);
}


int MateHelper::getFatherMap(int index) {
	if (index > fatherMap.size()) {
		fatherMap.push_back(++childSize);
	}

	return fatherMap.at(index);
}


int MateHelper::getBlendedMap(int motherIndex, int fatherIndex) {
	if (fatherIndex >= fatherMap.size() && motherIndex >= motherMap.size()) {
		childSize++;
		fatherMap.push_back(childSize);
		motherMap.push_back(childSize);
	}
	else if (fatherIndex > fatherMap.size()) {
		fatherMap.push_back(motherMap.at(motherIndex));
	}
	else if (motherIndex > motherMap.size()) {
		motherMap.push_back(fatherMap.at(fatherIndex));
	}

	return motherMap.at(motherIndex);
}

int MateHelper::GetChildSize() {
	return childSize;
}
