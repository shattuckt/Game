#include "GUIText.h"

GUIText::GUIText(std::string text, float fontSize, FontType* font, glm::vec2 position, float maxLineLength, bool centered) {
	this->textString = text;
	this->fontSize = fontSize;
	this->font = font;
	this->position = position;
	this->lineMaxSize = maxLineLength;
	this->centerText = centered;
	this->colour = glm::vec3(1, 0, 0);
	this->width = 0.5;
	this->edge = 0.1;
	this->borderWidth = 0.7; //default is no special efect
	this->borderEdge = 0.1;  //cannot be zero, use 0.1 as default 
	this->borderColour = glm::vec3(0, 0, 0); //white border by default
	this->offset = glm::vec2(0, 0); // no offset by default
}

void GUIText::remove() {
	//TextMaster.removeText(this);
}
FontType* GUIText::getFont() {
	return this->font;
}
void GUIText::setColour(float r, float g, float b) {
	this->colour = glm::vec3(r, g, b);
}
glm::vec3 GUIText::getColour() {
	return this->colour;
}

void GUIText::setBorderColour(float r, float g, float b) {
	this->borderColour = glm::vec3(r, g, b);
}
glm::vec3 GUIText::getBorderColour() {
	return this->borderColour;
}

void GUIText::setOffset(float x, float y) {
	this->offset = glm::vec2(x, y);
}

glm::vec2 GUIText::getOffset() {
	return this->offset;
}

void GUIText::setWidth(float width) {
	this->width = width;
}

float GUIText::getWidth() {
	return this->width;
}

void GUIText::setEdge(float edge) {
	this->edge = edge;
}

float GUIText::getEdge() {
	return this->edge;
}

void GUIText::setBorderWidth(float borderWidth) {
	this->borderWidth = borderWidth;
}

float GUIText::getBorderWidth() {
	return this->borderWidth;
}

void GUIText::setBorderEdge(float borderEdge) {
	this->borderEdge = borderEdge;
}

float GUIText::getBorderEdge() {
	return this->borderEdge;
}

int GUIText::getNumberOfLines() {
	return this->numberOfLines;
}
glm::vec2 GUIText::getPosition() {
	return this->position;
}
int GUIText::getMesh() {
	return this->textMeshVao;
}
void GUIText::setMeshInfo(int vao, int verticesCount) {
	this->textMeshVao = vao;
	this->vertexCount = verticesCount;
}
int GUIText::getVertexCount() {
	return this->vertexCount;
}
float GUIText::getFontSize() {
	return this->fontSize;
}
void GUIText::setNumberOfLines(int number) {
	this->numberOfLines = number;
}
bool GUIText::isCentered() {
	return this->centerText;
}
float GUIText::getMaxLineSize() {
	return this->lineMaxSize;
}
std::string GUIText::getTextString() {
	return this->textString;
}
