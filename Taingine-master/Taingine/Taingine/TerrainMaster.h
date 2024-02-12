#pragma once
#include "Terrain.h"
#include <string>
namespace TerrainHeights {
	class TerrainMaster {
	private:
		std::unordered_map<std::string, Terrain*> terrainElements;
		int xCoord;
		int zCoord;

	public:
		TerrainMaster(int xCoord, int zCoord);
		void generateTerrain(std::unordered_map<std::string, Terrain*> terrainElements);

		void increaseHeight(std::string coordinateKey, int height);
	};
}
