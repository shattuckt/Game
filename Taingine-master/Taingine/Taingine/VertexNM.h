#pragma once
#include <glm-0.9.8.5/glm/glm.hpp>
#include <vector>
#include <iostream>
#include "DuplicateVertexNM.h"

//The following is meant to emulate object instantiation of the local type VertexVM
class DuplicateVertex;

class VertexNM {
private:

	glm::vec3 position;
	unsigned int textureIndex;
	unsigned int normalIndex;

	int index;
	float length;
	VertexNM* duplicateVertex = NULL;
	std::vector<glm::vec3> tangents;
	glm::vec3 averagedTangent;

public:
	VertexNM(int index, glm::vec3 position);
	VertexNM() {};

	int getIndex();
	float getLength();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);
	glm::vec3 getPosition();
	int getTextureIndex();
	int getNormalIndex();
	VertexNM* duplicate(int newIndex);
	VertexNM* getDuplicateVertex();
	void setDuplicateVertex(VertexNM* dupVertex);

	void addTangent(glm::vec3 tangent);
	void averageTangents();
	glm::vec3 getAverageTangent();

	~VertexNM();
};

