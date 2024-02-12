#include "Character.h"

Character::Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize,
	double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance) {

	this->id = id;
	this->xTextureCoord = xTextureCoord;
	this->yTextureCoord = yTextureCoord;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->xMaxTextureCoord = xTexSize + xTextureCoord;
	this->yMaxTextureCoord = yTexSize + yTextureCoord;
	this->xAdvance = xAdvance;
}

int Character::getID() {
	return id;
}
double Character::getxTextureCoord() {
	return xTextureCoord;
}
double Character::getyTextureCoord() {
	return yTextureCoord;
}
double Character::getxMaxTextureCoord() {
	return xMaxTextureCoord;
}
double Character::getyMaxTextureCoord() {
	return yMaxTextureCoord;
}
double Character::getxOffset() {
	return xOffset;
}
double Character::getyOffset() {
	return yOffset;
}
double Character::getSizeX() {
	return sizeX;
}
double Character::getSizeY() {
	return sizeY;
}
double Character::getxAdvance() {
	return xAdvance;
}
