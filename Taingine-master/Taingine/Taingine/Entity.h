#pragma once
#include <glm-0.9.8.5\glm\glm.hpp>
#include "TexturedModel.h"
//#include <iostream>
class Entity
{
protected:

	TexturedModel model;
	glm::vec3 position;
	float rotX, rotY, rotZ;
	float scale;

	int textureIndex;

public:
	Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	Entity(TexturedModel model, int index, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	Entity(void);
	float getTextureXOffset();
	float getTextureYOffset();
	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);


	void setModel(TexturedModel model);
	void setPosition(glm::vec3 position);
	void setRotX(float rotX);
	void setRotY(float rotY);
	void setRotZ(float rotZ);
	void setScale(float scale);

	TexturedModel getModel();
	glm::vec3 getPosition();
	float getRotX();
	float getRotY();
	float getRotZ();
	float getScale();
	float getTextureIndex();

	~Entity(void);
};

