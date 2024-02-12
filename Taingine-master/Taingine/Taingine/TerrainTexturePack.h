#pragma once
#include "TerrainTexture.h"
class TerrainTexturePack
{
private:

	TerrainTexture backgroundTextures;
	TerrainTexture rTextures;
	TerrainTexture gTextures;
	TerrainTexture bTextures;

public:
	TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture);
	TerrainTexturePack(void) {};
	TerrainTexture getBackgroundTexture();
	TerrainTexture getrTexture();
	TerrainTexture getgTexture();
	TerrainTexture getbTexture();

	void setBackgroundTexture(TerrainTexture backgroundTexture);
	void setrTexture(TerrainTexture rTexture);
	void setgTexture(TerrainTexture gTexture);
	void setbTexture(TerrainTexture bTexture);



	~TerrainTexturePack(void);
};

