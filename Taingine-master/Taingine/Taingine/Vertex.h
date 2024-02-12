#pragma once
#include <glm-0.9.8.5/glm/glm.hpp>
#include <vector>
#include <iostream>
#include "DuplicateVertex.h"

//The following is meant to emulate object instantiation of the local type VertexVM
class DuplicateVertex;

class Vertex {
private:

	glm::vec3 position;
	unsigned int textureIndex;
	unsigned int normalIndex;

	int index;
	float length;
	Vertex* duplicateVertex = NULL;

public:
	Vertex(int index, glm::vec3 position);
	Vertex();

	int getIndex();
	float getLength();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);
	glm::vec3 getPosition();
	int getTextureIndex();
	int getNormalIndex();
	Vertex* duplicate(int newIndex);
	Vertex* getDuplicateVertex();
	void setDuplicateVertex(Vertex* dupVertex);

	~Vertex();
};