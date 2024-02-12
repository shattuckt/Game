#include "HeightsGenerator.h"

const float AMPLITUDE = 100.0f;
const int OCTAVES = 3;
const float ROUGHNESS = 0.3f;

HeightsGenerator::HeightsGenerator() {
	srand(time(NULL));
	this->seed = (float)rand();
	std::cout << "seed = " << seed << std::endl;

}

float HeightsGenerator::generateHeight(int x, int z) {

	//return getSmoothNoise(x, z) * AMPLITUDE;

	//std::cout << "test 1 " << getNoise(5, 14) << std::endl;
	//std::cout << "test 2 " << getNoise(5, 14) << std::endl;
	//std::cout << "test 3 " << getNoise(6, 14) << std::endl;
	//float height = getNoise(x, z) * AMPLITUDE;
	//std::cout << "Params: " << x << "/" << z << std::endl;
	//std::cout << "Height = " << height << std::endl;
	std::string key = std::to_string(x).append("-").append(std::to_string(z));
	std::unordered_map<std::string, float>::iterator iter = TerrainHeights::terrainHeights.find(key);
	if (iter != TerrainHeights::terrainHeights.end()) {
		return iter->second;
	}

	//float height = getNoise(x, z) * AMPLITUDE;

	float total = getInterpolatedNoise(x / 16.0f, z / 16.0f) * AMPLITUDE;
	//total += getInterpolatedNoise(x / 2.0f, z / 2.0f) * AMPLITUDE/3.0f;
	//total += getInterpolatedNoise(x, z) * AMPLITUDE / 9.0f;

	key = std::to_string(x).append("-").append(std::to_string(z));
	TerrainHeights::terrainHeights[key] = total;
	//std::cout << "coords " << key << " just added to map" << std::endl;
	//if (count % 100000 == 0) {
	//if (true){
		//std::cout << "creating new - count: " << count << std::endl;
		//std::cout << "total that was JUST pushed " << height << std::endl;
		//std::cout << "Height using key : " << key << " = " << TerrainHeights::terrainHeights[key] << std::endl;
	//}
	//count += 1;
	return total;
}

float HeightsGenerator::getInterpolatedNoise(float x, float z) {
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(intX, intZ);             //top left
	float v2 = getSmoothNoise(intX + 1, intZ);         //top right
	float v3 = getSmoothNoise(intX, intZ + 1);         //bottom left
	float v4 = getSmoothNoise(intX + 1, intZ + 1);     //bottom right
	float i1 = interpolate(v1, v2, fracX);             
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}

float HeightsGenerator::interpolate(float a, float b, float blend) {
	double theta = blend * M_PI;
	float f = (float)(1.0f - cos(theta)) * 0.5f;  //new blend factor - value between 0 - 1
	return a * (1.0f - f) + b * f;                //linear interpolation formula
}

float HeightsGenerator::getSmoothNoise(int x, int z) {
	float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1) + getNoise(x - 1, z + 1) + getNoise(x + 1, z + 1)) / 16.0f;
	float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1)	+ getNoise(x, z + 1)) / 8.0f;
	float center = getNoise(x, z) / 4.0f;
	return corners + sides + center;
}

float HeightsGenerator::getNoise(int x, int z) {
	srand(x * 49632 + z * 325176 + seed);
	x ^= x << (rand() % 32);
	x ^= x >> (rand() % 32);
	x ^= x << (rand() % 32);

	srand(x * 325176 + z * 49632 + seed);
	z ^= z << (rand() % 32);
	z ^= z >> (rand() % 32);
	z ^= z << (rand() % 32);
	int xorResult = z ^ x ^ seed;
	float result = (xorResult / (float)INT_MAX);
	return result;
}

