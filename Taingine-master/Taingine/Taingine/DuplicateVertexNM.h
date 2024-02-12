#pragma once
#include <glm-0.9.8.5\glm\glm.hpp>
#include <vector>

class VertexNM;

class DuplicateVertexNM {
private:

	glm::vec3 position;
	unsigned int textureIndex;
	unsigned int normalIndex;
	int index;
	float length;
	std::vector<glm::vec3> tangents;
	glm::vec3 averagedTangent;

public:
	DuplicateVertexNM(int index, glm::vec3 position);
	DuplicateVertexNM();

	int getIndex();
	float getLength();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);
	glm::vec3 getPosition();
	int getTextureIndex();
	int getNormalIndex();
	~DuplicateVertexNM();
};

