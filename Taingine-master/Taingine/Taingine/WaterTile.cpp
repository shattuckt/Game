#include "WaterTile.h"

const int TILE_SIZE = 2000;

WaterTile::WaterTile(float centerX, float heights, float centerZ) {
	x = centerX;
	z = centerZ;
	height = heights;
}
float WaterTile::getHeight() {
	return height;
}
float WaterTile::getX() {
	return x;
}
float WaterTile::getZ() {
	return z;
}
float WaterTile::getTileSize() {
	return TILE_SIZE;
}

WaterTile::~WaterTile(void)
{
}
