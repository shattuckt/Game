#pragma once
#include "TexturedModel.h"
#include "TerrainTexturePack.h"
#include "Loader.h"
#include "Maths.h"
#include "HeightsGenerator.h"
//#include <glm-0.9.8.5\glm\glm.hpp>
//#include <vector>

class Terrain
{
private:


	float gridX;
	float gridZ;
	RawModel models;
	TerrainTexturePack* texturePacks;
	TerrainTexture blendMaps;
	float terrainSize;

	HeightsGenerator* heightsGenerator;

public:
	Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack* texturePack, TerrainTexture blendMap, std::string heightMap, HeightsGenerator* heightsGenerator);
	Terrain() {}
	RawModel generateTerrain(Loader loader, std::string heightMap);
	glm::vec3 calculateNormal(int x, int z);
	float getHeight(int x, int z);
	float getX();
	float getZ();
	float getTerrainSize();
	HeightsGenerator* getHeightsGenerator();
	RawModel getModel();
	TerrainTexturePack* getTexturePacks();
	TerrainTexture getBlendMap();
	~Terrain(void);
};

