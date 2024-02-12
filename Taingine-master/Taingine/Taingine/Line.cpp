#include "Line.h"

Line::Line(double spaceWidth, double fontSize, double maxLength) {
	this->spaceSize = spaceWidth * fontSize;
	this->maxLength = maxLength;
}
bool Line::attemptToAddWord(Word* word) {
	double additionalLength = word->getWordWidth();
	std::cout << "Attempt to add word vals: \nspaceSize : " << this->spaceSize <<
		"\nmaxLength " << this->maxLength << std::endl;
	additionalLength += !words.empty() ? spaceSize : 0;
	std::cout << "currentLineLength " << currentLineLength <<
		"\nadditionalLength " << additionalLength << std::endl;
	if (currentLineLength + additionalLength <= maxLength) {
		words.push_back(word);
		currentLineLength += additionalLength;
		return true;
	}
	else {
		return false;
	}
}
double Line::getMaxLength() {
	return maxLength;
}
double Line::getLineLength() {
	return currentLineLength;
}
std::vector<Word*> Line::getWords() {
	return words;
}
