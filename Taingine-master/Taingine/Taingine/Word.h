#pragma once
#include <vector>
#include "Character.h"
class Word
{
private:
	std::vector<Character*> characters;
	double width = 0;
	double fontSize;
public:
#pragma region Word(double fontSize)
	/// Create a new empty word.
	/// param fontSize - the font size of the text which this word is in.
	Word(double fontSize);
#pragma endregion

#pragma region void addCharacter(Character* character)
	/// Adds a character to the end of the current word and increases the screen-space width of the word.
	/// param character - the character to be added.
	void addCharacter(Character* character);
#pragma endregion

#pragma region std::vector<Character*> getCharacters()
	/// return The list of characters in the word.
	std::vector<Character*> getCharacters();
#pragma endregion

#pragma region double getWordWidth()
	/// return The list of characters in the word.
	double getWordWidth();
#pragma endregion
};

