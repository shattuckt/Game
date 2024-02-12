#pragma once
#include <vector>

class ModelDataNM {

private:
	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<float> tangents;
	std::vector<unsigned int> indices;
	float furthestPoint;

public:
	ModelDataNM(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<float> tangents, std::vector<unsigned int> indices, float furthestPoint);

	std::vector<float> getVertices();
	std::vector<float> getTextureCoords();
	std::vector<float> getNormals();
	std::vector<float> getTangents();
	std::vector<unsigned int> getIndices();
	float getFurthestPoint();

	~ModelDataNM();
};

