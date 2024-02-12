#pragma once
#include <vector>


class MateHelper {
private:
	std::vector<int> motherMap;
	std::vector<int> fatherMap;
	int childSize = 0;

public:
	MateHelper(int ioSize);
	~MateHelper();

	int getMotherMap(int index);
	int getFatherMap(int index);
	int getBlendedMap(int motherIndex, int fatherIndex);
	int GetChildSize();
};

