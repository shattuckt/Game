#pragma once
#include <iostream>
#include <exception>


struct NullFactoryReferenceException : public std::exception {
	const char* what() const throw() {
		return "A reference to an IOutpurNeuronFactory was null.";
	}
};
