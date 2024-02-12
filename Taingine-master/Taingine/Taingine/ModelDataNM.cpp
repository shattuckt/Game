#include "ModelDataNM.h"

ModelDataNM::ModelDataNM(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<float> tangents, std::vector<unsigned int> indices, float furthestPoint) {
	this->vertices = vertices;
	this->textureCoords = textureCoords;
	this->normals = normals;
	this->tangents = tangents;
	this->indices = indices;
	this->furthestPoint = furthestPoint;
}

std::vector<float> ModelDataNM::getVertices() {
	return vertices;
}
std::vector<float> ModelDataNM::getTextureCoords() {
	return textureCoords;
}
std::vector<float> ModelDataNM::getTangents() {
	return tangents;
}
std::vector<float> ModelDataNM::getNormals() {
	return normals;
}
std::vector<unsigned int> ModelDataNM::getIndices() {
	return indices;
}
float ModelDataNM::getFurthestPoint() {
	return furthestPoint;
}

ModelDataNM::~ModelDataNM()
{
}
