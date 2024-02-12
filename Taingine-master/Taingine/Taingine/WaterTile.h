#pragma once
class WaterTile
{
private:
	float height;
	float x, z;

public:
	WaterTile(float centerX, float heights, float centerZ);
	float getHeight();
	float getX();
	float getZ();
	float getTileSize();

	~WaterTile(void);
};

