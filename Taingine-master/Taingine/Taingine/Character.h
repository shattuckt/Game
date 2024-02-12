#pragma once
class Character
{
private:

#pragma region objectVariables
	int id;                   // the ASCII value of the character.
	double xTextureCoord;     // the x texture coordinate for the top left corner of the character in the texture atlas.
	double yTextureCoord;     // the y texture coordinate for the top left corner of the character in the texture atlas.
	double xMaxTextureCoord;  // the width of the character in the texture atlas.
	double yMaxTextureCoord;  // the height of the character in the texture atlas.
	double xOffset;           // the x distance from the curser to the left edge of the character's quad.
	double yOffset;           // the y distance from the curser to the top edge of the character's quad.
	double sizeX;             // the width of the character's quad in screen space.
	double sizeY;             // the height of the character's quad in screen space.
	double xAdvance;          // how far in pixels the cursor should advance after adding this character.
#pragma endregion

public:
	Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize,
		double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance);
	Character(void) {};

	int getID();
	double getxTextureCoord();
	double getyTextureCoord();
	double getxMaxTextureCoord();
	double getyMaxTextureCoord();
	double getxOffset();
	double getyOffset();
	double getSizeX();
	double getSizeY();
	double getxAdvance();
	


};

