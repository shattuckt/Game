#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <iostream>
#include "TerrainHeights.h"
#include <time.h>
#include <string>

class HeightsGenerator
{
private:
	int seed;
	int tempSeed = 0;
	int count = 0;

public:
	HeightsGenerator();

	float generateHeight(int x, int z);

#pragma region float getInterpolatedNoise(float x, float z);
	/// Returns the height of a coordinate based on the surrounding heights.
	/// This is done by evaluating the height of four surrounding vertices
	/// once found, we interpolate two edges to create points on those edges that are parallel with the original coordinate
	/// 
	float getInterpolatedNoise(float x, float z);
#pragma endregion

#pragma region float interpolate(float a, float b, float blend);
	/// This is cosine interpolation
	/// The point of it is to add a bit of curve between two points.
	float interpolate(float a, float b, float blend);
#pragma endregion

	float getSmoothNoise(int x, int z);

#pragma region float getNoise(int x, int z);
	/// Takes an x and z coordinate and returns a value between -1 and 1. 
	/// The same coordinates being fed in MUST return the same value.
	/// This is due to the noise value depicting the heights of the terrain. 
	float getNoise(int x, int z); 
#pragma endregion



};

