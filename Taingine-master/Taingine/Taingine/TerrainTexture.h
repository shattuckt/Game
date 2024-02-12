#pragma once
class TerrainTexture
{
private:

	int textureIDs;

public:
	TerrainTexture(int textureID);
	TerrainTexture(void) {};

	int getTextureID();
	void setTextureID(int textureID);
	~TerrainTexture(void);
};

