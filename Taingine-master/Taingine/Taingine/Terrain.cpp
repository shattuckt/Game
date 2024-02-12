#include "Terrain.h"

const float TERRAINSIZE = 1000;

const int VERTEX_COUNT = 16; //this is how many vertices there are along the side of a tile

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack* texturePack, TerrainTexture blendMap, std::string heightMap, HeightsGenerator* heightsGenerator) {
	this->texturePacks = texturePack;
	this->blendMaps = blendMap;
	this->gridX = gridX * TERRAINSIZE;
	this->gridZ = gridZ * TERRAINSIZE;
	this->heightsGenerator = heightsGenerator;
	models = generateTerrain(loader, heightMap);
	terrainSize = TERRAINSIZE;
	
}

RawModel Terrain::generateTerrain(Loader loader, std::string heightMap) {
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<unsigned int> indices(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
	int vertexPointer = 0;
	for (int z = 0; z<VERTEX_COUNT; z++) {
		for (int x = 0; x<VERTEX_COUNT; x++) {
			float coordX = (float)x / ((float)VERTEX_COUNT - 1);
			float coordZ = (float)z / ((float)VERTEX_COUNT - 1);

			vertices[vertexPointer * 3] = coordX * TERRAINSIZE;
			vertices[vertexPointer * 3 + 2] = coordZ * TERRAINSIZE;
			vertices[vertexPointer * 3 + 1] = getHeight(int(vertices[vertexPointer * 3] + this->gridX), int(vertices[vertexPointer * 3 + 2] + this->gridZ));
			//std::cout << "Vertices: " << vertices[vertexPointer * 3] << "/" << vertices[vertexPointer * 3 + 1] << "/" << vertices[vertexPointer * 3 + 2] << std::endl;
			glm::vec3 normal = calculateNormal(x, z);
			//normals[vertexPointer * 3] = 0;
			//normals[vertexPointer * 3 + 1] = 1;
			//normals[vertexPointer * 3 + 2] = 0;
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			textureCoords[vertexPointer * 2] = (float)x / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)z / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	float* verticesArray = &vertices[0];
	float* texturedArray = &textureCoords[0];
	float* normalArray = &normals[0];
	unsigned int* indicesArray = &indices[0];

	return loader.loadToVAO(vertices, textureCoords, normals, indices);

}

//By default, all normals on the texture point straight up. which would make everything be one color
glm::vec3 Terrain::calculateNormal(int x, int z) {
	float heightL = getHeight(x - 1, z);
	float heightR = getHeight(x + 1, z);
	float heightD = getHeight(x, z - 1);
	float heightU = getHeight(x, z + 1);
	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
	glm::normalize(normal); //ensure the vector is less than 1... 
	return normal;
}
float Terrain::getHeight(int x, int z) {
	return this->heightsGenerator->generateHeight(x, z);
}

float Terrain::getX() {
	return this->gridX;
}
float Terrain::getZ() {
	return this->gridZ;
}
float Terrain::getTerrainSize() {
	return terrainSize;
}
RawModel Terrain::getModel() {
	return models;
}
TerrainTexturePack* Terrain::getTexturePacks() {
	return texturePacks;
}
TerrainTexture Terrain::getBlendMap() {
	return blendMaps;
}

HeightsGenerator* Terrain::getHeightsGenerator() {
	return this->heightsGenerator;
}


Terrain::~Terrain(void)
{
}
