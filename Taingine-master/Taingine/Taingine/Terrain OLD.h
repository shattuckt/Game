#pragma once
#include "TexturedModel.h"
#include "TerrainTexturePack.h"
#include "Loader.h"
#include "Maths.h"
//#include <glm-0.9.8.5\glm\glm.hpp>
//#include <vector>

class Terrain
{
private:

	float x;
	float z;
	std::vector<std::vector<float>> heights;
	RawModel models;
	TerrainTexturePack texturePacks;
	TerrainTexture blendMaps;
	float terrainSize;

public:
	Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, std::string heightMap);
	Terrain() {}
	RawModel generateTerrain(Loader loader, std::string heightMap);
	glm::vec3 calculateNormal(int x, int z, unsigned char* image, int width, int height, int nrChannels);
	float getHeight(int x, int y, unsigned char* image, int width, int height, int nrChannels);
	float getX();
	float getZ();
	float getTerrainSize();
	RawModel getModel();
	TerrainTexturePack getTexturePacks();
	TerrainTexture getBlendMap();
	float getHeightOfTerrain(float worldX, float worldZ);
	~Terrain(void);
};

