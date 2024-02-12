#include "Word.h"

Word::Word(double fontSize) {
	this->fontSize = fontSize;
}
void Word::addCharacter(Character* character) {
	characters.push_back(character);
	width += character->getxAdvance() * fontSize;
}
std::vector<Character*> Word::getCharacters() {
	return this->characters;
}
double Word::getWordWidth() {
	return this->width;
}