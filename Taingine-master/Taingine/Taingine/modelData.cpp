#include "ModelData.h"



ModelData::ModelData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices, float furthestPoint) {
	this->vertices = vertices;
	this->textureCoords = textureCoords;
	this->normals = normals;
	this->indices = indices;
	this->furthestPoint = furthestPoint;
}

std::vector<float> ModelData::getVertices() {
	return vertices;
}
std::vector<float> ModelData::getTextureCoords() {
	return textureCoords;
}
std::vector<float> ModelData::getNormals() {
	return normals;
}
std::vector<unsigned int> ModelData::getIndices() {
	return indices;
}
float ModelData::getFurthestPoint() {
	return furthestPoint;
}

ModelData::~ModelData()
{
}
