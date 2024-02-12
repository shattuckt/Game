#include "TerrainTexturePack.h"


TerrainTexturePack::TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture) {
	backgroundTextures = backgroundTexture;
	rTextures = rTexture;
	gTextures = gTexture;
	bTextures = bTexture;
}
TerrainTexture TerrainTexturePack::getBackgroundTexture() {
	return backgroundTextures;
}
TerrainTexture TerrainTexturePack::getrTexture() {
	return rTextures;
}
TerrainTexture TerrainTexturePack::getgTexture() {
	return gTextures;
}
TerrainTexture TerrainTexturePack::getbTexture() {
	return bTextures;
}

void TerrainTexturePack::setBackgroundTexture(TerrainTexture backgroundTexture) {
	backgroundTextures = backgroundTexture;
}
void TerrainTexturePack::setrTexture(TerrainTexture rTexture) {
	rTextures = rTexture;
}
void TerrainTexturePack::setgTexture(TerrainTexture gTexture) {
	gTextures = gTexture;
}
void TerrainTexturePack::setbTexture(TerrainTexture bTexture) {
	bTextures = bTexture;
}

TerrainTexturePack::~TerrainTexturePack(void)
{
}
