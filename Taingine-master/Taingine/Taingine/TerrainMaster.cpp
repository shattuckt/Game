#include "TerrainMaster.h"

const float TERRAINSIZE = 1000;

const int VERTEX_COUNT = 16; //this is how many vertices there are along the side of a tile

using namespace TerrainHeights;

TerrainMaster::TerrainMaster(int xCoord, int zCoord) {
	this->xCoord = xCoord;
	this->zCoord = zCoord;
}
void TerrainMaster::generateTerrain(std::unordered_map<std::string, Terrain*> terrainElements) {

}

void TerrainMaster::increaseHeight(std::string coordinateKey, int height) {

}