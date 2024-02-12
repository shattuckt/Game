#include "DuplicateVertexNM.h"

const int NO_INDEX = -1;

DuplicateVertexNM::DuplicateVertexNM(int index, glm::vec3 position) {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	this->index = index;
	this->position = position;
	this->length = position.length();
}

DuplicateVertexNM::DuplicateVertexNM() {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	this->index = NULL;
	this->position = glm::vec3(-1, -1, -1);
	this->length = -1.0f;
}

int DuplicateVertexNM::getIndex() {
	return index;
}

float DuplicateVertexNM::getLength() {
	return length;
}

bool DuplicateVertexNM::isSet() {
	return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool DuplicateVertexNM::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) {
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

void DuplicateVertexNM::setTextureIndex(int textureIndex) {
	this->textureIndex = textureIndex;
}

void DuplicateVertexNM::setNormalIndex(int normalIndex) {
	this->normalIndex = normalIndex;
}

glm::vec3 DuplicateVertexNM::getPosition() {
	return position;
}

int DuplicateVertexNM::getTextureIndex() {
	return textureIndex;
}

int DuplicateVertexNM::getNormalIndex() {
	return normalIndex;
}

DuplicateVertexNM::~DuplicateVertexNM()
{
}