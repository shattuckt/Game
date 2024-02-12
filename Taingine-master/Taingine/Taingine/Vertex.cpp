#include "Vertex.h"

const int NO_INDEX = -1;

Vertex::Vertex(int index, glm::vec3 position) {
	textureIndex = NO_INDEX;
	normalIndex = NO_INDEX;
	this->duplicateVertex = NULL;
	this->index = index;
	this->position = position;
	this->length = position.length();
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

int Vertex::getIndex() {
	return index;
}

float Vertex::getLength() {
	return length;
}

bool Vertex::isSet() {
	return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) {
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

void Vertex::setTextureIndex(int textureIndex) {
	this->textureIndex = textureIndex;
}

void Vertex::setNormalIndex(int normalIndex) {
	this->normalIndex = normalIndex;
}

glm::vec3 Vertex::getPosition() {
	return position;
}

int Vertex::getTextureIndex() {
	return textureIndex;
}

int Vertex::getNormalIndex() {
	return normalIndex;
}

Vertex* Vertex::duplicate(int newIndex) {
	Vertex* vertex = new Vertex(newIndex, position);
	return vertex;
}

Vertex* Vertex::getDuplicateVertex() {
	return duplicateVertex;
}
void Vertex::setDuplicateVertex(Vertex* duplicateVertex) {
	this->duplicateVertex = duplicateVertex;
}

Vertex::~Vertex()
{
}
