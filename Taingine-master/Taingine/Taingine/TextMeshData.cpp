#include "TextMeshData.h"


TextMeshData::TextMeshData(std::vector<float>  vertexPositions, std::vector<float> textureCoords) {
	this->vertexPositions = vertexPositions;
	this->textureCoords = textureCoords;
}
std::vector<float> TextMeshData::getVertexPositions() {
	return this->vertexPositions;
}
std::vector<float> TextMeshData::getTextureCoords() {
	return this->textureCoords;
}
int TextMeshData::getVertexCount() {
	return this->vertexPositions.size() / 2;
}
