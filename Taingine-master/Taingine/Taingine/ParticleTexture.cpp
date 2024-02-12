#include "ParticleTexture.h"
ParticleTexture::ParticleTexture(int textureID, int numberOfRows, bool additive) {
	this->textureID = textureID;
	this->numberOfRows = numberOfRows;
	this->additive = additive;
}

int ParticleTexture::getTextureID() {
	return this->textureID;
}
int ParticleTexture::getNumberOfRows() {
	return this->numberOfRows;
}
bool ParticleTexture::usesAdditiveBlending() {
	return this->additive;
}