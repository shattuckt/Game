#pragma once
#include "MetaFile.h"
#include "TextMeshData.h"
#include "Line.h"
#include "GUIText.h"

class FontType;
class GUIText;

class TextMeshCreator
{
private:

	MetaFile* metaData;
	DisplayManager* display;
	int textureAtlas;

	std::vector<Line*> lines;
	std::vector<float> vertices;
	std::vector<float> textureCoords;

public:
#pragma region TextMeshCreator(std::string metaFile, DisplayManager* display)
/// Takes in an unloaded textand calculate all of the vertices for the quads
/// on which this text will be rendered.The vertex positionsand texture
/// coordsand calculated based on the information from the font file.
/// param fileName - the unloaded text.
/// return     - Information about the vertices of all the quads.
	TextMeshCreator(std::string fileName, DisplayManager* display);
#pragma endregion

//TextMeshCreator(std::string metaFile, DisplayManager* display, int textureAtlas);
TextMeshCreator(void) {};
#pragma region TextMeshData* createTextMesh(GUIText* text)
	TextMeshData* createTextMesh(GUIText* text);
#pragma endregion

#pragma region std::vector<Line*> createStructure(GUIText* text) 
	std::vector<Line*> createStructure(GUIText* text);
#pragma endregion

#pragma region void completeStructure(Line* currentLine, Word* currentWord, GUIText* text)
	void completeStructure(Line* currentLine, Word* currentWord, GUIText* text);
#pragma endregion

#pragma region TextMeshData* createQuadVertices(GUIText text, std::vector<Line> lines)
	TextMeshData* createQuadVertices(GUIText* text, std::vector<Line*> lines);
#pragma endregion

#pragma region void addVerticesForCharacter(double curserX, double curserY, Character* character, double fontSize, std::vector<Float> vertices)
	void addVerticesForCharacter(double curserX, double curserY, Character* character, double fontSize);
#pragma endregion

#pragma region void addVertices(double x, double y, double maxX, double maxY)
	void addVertices(double x, double y, double maxX, double maxY);
#pragma endregion

#pragma region void addTexCoords(double x, double y, double maxX, double maxY)
	void addTexCoords(double x, double y, double maxX, double maxY);
#pragma endregion

	int getTextureAtlas();
};


