#pragma once
#include "TextMeshCreator.h"
#include "DisplayManager.h"

class GUIText;
class TextMeshCreator;

class FontType
{
private:
	int textureAtlas;         // the ID of the font atlas texture.
	DisplayManager* display;
	TextMeshCreator* textMeshCreator;  // the font file containing information about each character in the texture atlas.
public:
	FontType(int textureAtlas, std::string fontFile, DisplayManager* display);
	FontType(void) {};
	int getTextureAtlas();                          // return The font texture atlas.

#pragma region TextMeshData loadText(GUIText text)
/// Takes in an unloaded textand calculate all of the vertices for the quads
/// on which this text will be rendered.The vertex positionsand texture
/// coordsand calculated based on the information from the font file.
/// param text - the unloaded text.
/// return     - Information about the vertices of all the quads used in the loadToVao method
	TextMeshData* loadText(GUIText* text);
};
#pragma endregion