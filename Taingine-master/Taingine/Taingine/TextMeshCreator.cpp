#include "TextMeshCreator.h"

const double LINE_HEIGHT = 0.03f;
const int SPACE_ASCII = 32;

TextMeshCreator::TextMeshCreator(std::string fileName, DisplayManager* display) {
	this->display = display;
	this->metaData = new MetaFile(fileName, display);
}

//TextMeshCreator::TextMeshCreator(std::string metaFile, DisplayManager* display, int textureAtlas) {
//	this->metaData = new MetaFile(metaFile, display);
//	this->textureAtlas = textureAtlas;
//}

int TextMeshCreator::getTextureAtlas() {
	return textureAtlas;
}


TextMeshData* TextMeshCreator::createTextMesh(GUIText* text) {
	std::vector<Line*> lines = createStructure(text);
	TextMeshData* data = createQuadVertices(text, lines);
	std::cout << "$$$$$$$$$textMeshData sizes - vertexPos = " << data->getVertexPositions().size() <<
		"\ntextreCords = " << data->getTextureCoords().size() << std::endl;
	return data;
}
std::vector<Line*> TextMeshCreator::createStructure(GUIText* text) {
	//std::vector<char> stringToVector(text->getTextString().begin(), text->getTextString().end());
	//lines.clear();
	Line* currentLine = new Line(metaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize());
	Word* currentWord = new Word(text->getFontSize());
	std::string textToRender = text->getTextString();
	for (int x = 0; x < textToRender.size(); x++){
		std::cout << "textToRender[" << x << "] : " << textToRender[x] << std::endl;
		int ascii = (int)textToRender[x];
		if (ascii == SPACE_ASCII) {
			bool added = currentLine->attemptToAddWord(currentWord);
			if (!added) {
				lines.push_back(currentLine);
				currentLine = new Line(metaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize());
				currentLine->attemptToAddWord(currentWord);
			}
			currentWord = new Word(text->getFontSize());
			continue;
		}
		Character* character = metaData->getCharacter(ascii);
		currentWord->addCharacter(character);
	}
	//lines.push_back(currentLine);
	//std::cout << "lines.size = " << lines.size() << std::endl;
	completeStructure(currentLine, currentWord, text);
	//std::cout << "lines.size = " << lines.size() << std::endl;
	return lines;
}
void TextMeshCreator::completeStructure(Line* currentLine, Word* currentWord, GUIText* text) {
	bool added = currentLine->attemptToAddWord(currentWord);
	if (!added) {
		lines.push_back(currentLine);
		currentLine = new Line(metaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize());
		currentLine->attemptToAddWord(currentWord);
	}
	lines.push_back(currentLine);
}
TextMeshData* TextMeshCreator::createQuadVertices(GUIText* text, std::vector<Line*> lines) {
	text->setNumberOfLines(lines.size());
	double curserX = 0.0f;
	double curserY = 0.0f;

	std::cout << lines.size();
	for (int i = 0; i < lines.size(); i++) {
		if (text->isCentered()) {
			curserX = (lines[i]->getMaxLength() - lines[i]->getLineLength()) / 2;
		}
		for (Word* word : lines[i]->getWords()) {
			for (Character* letter : word->getCharacters()) {
				addVerticesForCharacter(curserX, curserY, letter, text->getFontSize());
				addTexCoords(letter->getxTextureCoord(), letter->getyTextureCoord(),
					letter->getxMaxTextureCoord(), letter->getyMaxTextureCoord());
				curserX += letter->getxAdvance() * text->getFontSize();
			}
			curserX += metaData->getSpaceWidth() * text->getFontSize();
		}
		curserX = 0;
		curserY += LINE_HEIGHT * text->getFontSize();
	}
	return new TextMeshData(vertices, textureCoords);
}
void TextMeshCreator::addVerticesForCharacter(double curserX, double curserY, Character* character, double fontSize) {
	double x = curserX + (character->getxOffset() * fontSize);
	double y = curserY + (character->getyOffset() * fontSize);
	double maxX = x + (character->getSizeX() * fontSize);
	double maxY = y + (character->getSizeY() * fontSize);
	double properX = (2 * x) - 1;
	double properY = (-2 * y) + 1;
	double properMaxX = (2 * maxX) - 1;
	double properMaxY = (-2 * maxY) + 1;
	addVertices(properX, properY, properMaxX, properMaxY);
}
void TextMeshCreator::addVertices(double x, double y, double maxX, double maxY) {
	this->vertices.push_back((float)x);
	this->vertices.push_back((float)y);
	this->vertices.push_back((float)x);
	this->vertices.push_back((float)maxY);
	this->vertices.push_back((float)maxX);
	this->vertices.push_back((float)maxY);
	this->vertices.push_back((float)maxX);
	this->vertices.push_back((float)maxY);
	this->vertices.push_back((float)maxX);
	this->vertices.push_back((float)y);
	this->vertices.push_back((float)x);
	this->vertices.push_back((float)y);
}
void TextMeshCreator::addTexCoords(double x, double y, double maxX, double maxY) {
	this->textureCoords.push_back((float)x);
	this->textureCoords.push_back((float)y);
	this->textureCoords.push_back((float)x);
	this->textureCoords.push_back((float)maxY);
	this->textureCoords.push_back((float)maxX);
	this->textureCoords.push_back((float)maxY);
	this->textureCoords.push_back((float)maxX);
	this->textureCoords.push_back((float)maxY);
	this->textureCoords.push_back((float)maxX);
	this->textureCoords.push_back((float)y);
	this->textureCoords.push_back((float)x);
	this->textureCoords.push_back((float)y);
}

