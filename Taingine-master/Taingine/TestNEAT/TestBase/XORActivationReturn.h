#pragma once
class XORActivationReturn {
private:
	int value = -1;
public:
	XORActivationReturn();
	~XORActivationReturn();

	int getValue();
	void setValue(int _value);
};

