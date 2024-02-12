#include "VertexNM.h"

const int NO_INDEX = -1;

VertexNM::VertexNM(int index, glm::vec3 position) {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	this->duplicateVertex = NULL;
	this->index = index;
	this->position = position;
	this->length = position.length();
	this->averagedTangent = glm::vec3(0, 0, 0);
	
}

/*Vertex::Vertex() {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	//this->dupVertex = DuplicateVertex(-1, glm::vec3(-1, -1, -1));
	this->duplicateVertex = NULL;
	this->index = NO_INDEX;
	this->position = glm::vec3(-1, -1, -1);
	this->length = -1.0f;

	//std::cout << "default VERTEX constructur called - dupVertex elements equal to: " <<
		//dupVertex.getIndex() << " position: " << dupVertex.getPosition().x << "//" <<
		//dupVertex.getPosition().y << "//" << dupVertex.getPosition().z << std::endl;
}*/

int VertexNM::getIndex() {
	return index;
}

float VertexNM::getLength() {
	return length;
}

bool VertexNM::isSet() {
	return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool VertexNM::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) {
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

void VertexNM::setTextureIndex(int textureIndex) {
	this->textureIndex = textureIndex;
}

void VertexNM::setNormalIndex(int normalIndex) {
	this->normalIndex = normalIndex;
}

glm::vec3 VertexNM::getPosition() {
	return position;
}

int VertexNM::getTextureIndex() {
	return textureIndex;
}

int VertexNM::getNormalIndex() {
	return normalIndex;
}

VertexNM* VertexNM::duplicate(int newIndex) {
	VertexNM* vertex = new VertexNM(newIndex, position);
	vertex->tangents = this->tangents;
	return vertex;
}

VertexNM* VertexNM::getDuplicateVertex() {
	return duplicateVertex;
}
void VertexNM::setDuplicateVertex(VertexNM* duplicateVertex) {
	this->duplicateVertex = duplicateVertex;
}

void VertexNM::addTangent(glm::vec3 tangent) {
	tangents.push_back(tangent);
}

void VertexNM::averageTangents() {
	if (tangents.empty()) {
		return;
	}
	for (int i = 0; i < tangents.size(); i++) { // was tangents.size() NOT 1
		averagedTangent = averagedTangent + tangents[i];

	}
	averagedTangent = glm::normalize(averagedTangent);
}

glm::vec3 VertexNM::getAverageTangent() {
	return averagedTangent;
}

VertexNM::~VertexNM()
{
}
