#pragma once
#include "Word.h"
#include <iostream>

class Line
{
private:
	double maxLength;
	double spaceSize;

	std::vector<Word*> words;
	double currentLineLength = 0;
public:
#pragma region Line(double spaceWidth, double fontSize, double maxLength)
	/// Creates an empty line.
	/// param spaceWidth - the screen - space width of a space character.
	/// param fontSize - the size of font being used.
	/// param maxLength - the screen - space maximum length of a line.
	Line(double spaceWidth, double fontSize, double maxLength);
#pragma endregion

#pragma region bool attemptToAddWord(Word* word)
	/// Attempt to add a word to the line. If the line can fit the word in
	///    without reaching the maximum line length then the word is addedand the
	///	   line length increased.
	/// param word - the word to try to add.
	/// return {@code true} if the word has successfully been added to the line.
	bool attemptToAddWord(Word* word);
#pragma endregion

#pragma region double getMaxLength()
	/// return The max length of the line.
	double getMaxLength();
#pragma endregion

#pragma region double getLineLength()
	/// return The current screen-space length of the line.
	double getLineLength();
#pragma endregion

#pragma region std::vector<Word*> getWords()
	/// return The list of words in the line.
	std::vector<Word*> getWords();
#pragma endregion

};

