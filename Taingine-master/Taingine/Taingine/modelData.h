#pragma once
#include <vector>

class ModelData {
private:
	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	float furthestPoint;

public:
	ModelData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices, float furthestPoint);

	std::vector<float> getVertices();
	std::vector<float> getTextureCoords();
	std::vector<float> getNormals();
	std::vector<unsigned int> getIndices();
	float getFurthestPoint();

	~ModelData();
};

