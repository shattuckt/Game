#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Character.h"
#include "DisplayManager.h"
#include "getPaths.h"
#include "FileUtility.h"
#include <string>
#include <sstream>

//#include "Loader.h"



/*typedef std::pair<int, Character> metaData;

struct hash_entity { //This is meant to return the hash of all 5 elements 
	size_t operator()(const metaData& metaData) const {
		int intID = metaData.first;
		Character character = metaData.second;
		return std::hash<int>()(intID) ^ std::hash<int>()(character.getID()) ^ std::hash<double>()(character.getxTextureCoord()) ^ std::hash<double>()(character.getyTextureCoord()) ^ std::hash<double>()(character.getxMaxTextureCoord())
			^ std::hash<double>()(character.getyMaxTextureCoord()) ^ std::hash<double>()(character.getxOffset()) ^ std::hash<double>()(character.getyOffset()) ^ std::hash<double>()(character.getSizeX())
			^ std::hash<double>()(character.getSizeY()) ^ std::hash<double>()(character.getxAdvance());
	}
};

struct equal_entity { //We now need to find if they are all equal or not... 
	bool operator()(const metaData& lhs, const metaData& rhs) const {
		int LintID = lhs.first;
		int RintID = rhs.first;
		Character leftCharacter = lhs.second;
		Character rightCharacter = rhs.second;
		return LintID == RintID && leftCharacter.getID() == rightCharacter.getID() && leftCharacter.getSizeX() == rightCharacter.getSizeX() &&
			leftCharacter.getSizeY() == rightCharacter.getSizeY() && leftCharacter.getxAdvance() == rightCharacter.getxAdvance() &&
			leftCharacter.getxMaxTextureCoord() == rightCharacter.getxMaxTextureCoord() && leftCharacter.getyMaxTextureCoord() == rightCharacter.getyMaxTextureCoord() &&
			leftCharacter.getxOffset() == rightCharacter.getxOffset() && leftCharacter.getyOffset() == rightCharacter.getyOffset() &&
			leftCharacter.getxTextureCoord() == rightCharacter.getxTextureCoord() && leftCharacter.getyTextureCoord() == leftCharacter.getyTextureCoord();
	}
};*/

class MetaFile
{
private:

	DisplayManager* display;

	double aspectRatio;

	double verticalPerPixelSize;
	double horizontalPerPixelSize;
	double spaceWidth;
	std::vector<int> padding;
	int paddingWidth;
	int paddingHeight;

	std::filebuf* fileReader;
	std::istream* stream;

	std::unordered_map<int, Character*> metaData;
	std::unordered_map<std::string, std::string> values;

public:
#pragma region MetaFile(std::string file, DisplayManager* display)
	/// Opens a font file in preparation for reading.
	/// param file - the font file.
	/// param width, height - needed so we dont have to pass the displayManager object into this
	MetaFile(std::string file, DisplayManager* display);
	MetaFile(); //default constructor
#pragma endregion

#pragma region double getSpaceWidth()
	double getSpaceWidth();
#pragma endregion

#pragma region Character* getCharacter(int ascii)
	Character* getCharacter(int ascii);
#pragma endregion

#pragma region bool processNextLine()
	/// Read in the next line and store the variable values.
	/// return {@code true} if the end of the file hasn't been reached.
	bool processNextLine();
#pragma endregion

#pragma region int getValueOfVariable(std::string variable)
	/// Gets the {@code int} value of the variable with a certain name on the current line.
	/// param variable - the name of the variable.
	/// return The value of the variable.
	int getValueOfVariable(std::string variable);
#pragma endregion

#pragma region std::vector<int> getValuesOfVariable(std::string variable)
	/// Gets the array of ints associated with a variable on the current line.
	/// param variable - the name of the variable.
	/// return The int array of values associated with the variable.
	std::vector<int> getValuesOfVariable(std::string variable);
#pragma endregion

#pragma region void close()
	/// Closes the font file after finishing reading.
	void close();
#pragma endregion

#pragma region void loadPaddingData()
	/// Loads the data about how much padding is used around each character in the texture atlas.
	void loadPaddingData();
#pragma endregion

#pragma region void loadLineSizes()
	/// Loads information about the line height for this font in pixels, and uses
	///		this as a way to find the conversion rate between pixels in the texture
	///		atlas and screen-space.
	void loadLineSizes();
#pragma endregion

#pragma region void loadCharacterData(int imageWidth)
	/// Loads in data about each character and stores the data in the {@link Character} class.
	///	param imageWidth - the width of the texture atlas in pixels.
	void loadCharacterData(int imageWidth);
#pragma endregion

#pragma region Character* loadCharacter(int imageSize)
	/// Loads all the data about one character in the texture atlas and converts
	///		it all from 'pixels' to 'screen-space' before storing.The effects of
	///		padding are also removed from the data.
	///	param imageSize - the size of the texture atlas in pixels.
	/// return The data about the character.
	Character* loadCharacter(int imageSize);
#pragma endregion
};

