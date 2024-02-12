#include "TerrainTexture.h"


TerrainTexture::TerrainTexture(int textureID) {
	textureIDs = textureID;
}
int TerrainTexture::getTextureID() {
	return textureIDs;
}
void TerrainTexture::setTextureID(int textureID) {
	textureIDs = textureID;
}

TerrainTexture::~TerrainTexture(void)
{
}
