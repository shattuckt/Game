#include "DuplicateVertex.h"

const int NO_INDEX = -1;

DuplicateVertex::DuplicateVertex(int index, glm::vec3 position) {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	this->index = index;
	this->position = position;
	this->length = position.length();
}

DuplicateVertex::DuplicateVertex() {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	this->index = NULL;
	this->position = glm::vec3(-1, -1, -1);
	this->length = -1.0f;
}

int DuplicateVertex::getIndex() {
	return index;
}

float DuplicateVertex::getLength() {
	return length;
}

bool DuplicateVertex::isSet() {
	return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool DuplicateVertex::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) {
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

void DuplicateVertex::setTextureIndex(int textureIndex) {
	this->textureIndex = textureIndex;
}

void DuplicateVertex::setNormalIndex(int normalIndex) {
	this->normalIndex = normalIndex;
}

glm::vec3 DuplicateVertex::getPosition() {
	return position;
}

int DuplicateVertex::getTextureIndex() {
	return textureIndex;
}

int DuplicateVertex::getNormalIndex() {
	return normalIndex;
}

DuplicateVertex::~DuplicateVertex()
{
}