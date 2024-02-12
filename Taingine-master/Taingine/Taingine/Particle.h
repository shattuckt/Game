#pragma once
#include <glm-0.9.8.5/glm/glm.hpp>
#include "DisplayManager.h"
#include "Camera.h"
#include "ParticleTexture.h"

class Particle
{
private:
	glm::vec3 position;
	glm::vec3 velocity;
	float gravityEffect;
	float lifeLength;
	float rotation;
	float scale;

	ParticleTexture* texture;

	glm::vec2 texOffset1;
	glm::vec2 texOffset2;
	float blend;

	DisplayManager* display;

	float elapsedTime = 0;
	float distance;

	glm::vec3 change;

public:
	Particle(ParticleTexture* texture, glm::vec3 position, glm::vec3 velocity, float gravityEffect,
		float lifeLength,	float roation, float scale, DisplayManager* display);

	void setActive(ParticleTexture* texture, glm::vec3 position, glm::vec3 velocity, float gravityEffect,
		float lifeLength, float roation, float scale);

	ParticleTexture* getTexture();
	glm::vec3 getPosition();
	float getRotation();
	float getScale();
	glm::vec2 getTexOffset1();
	glm::vec2 getTexOffset2();
	float getBlend();
	float getDistance();

	void updateTextureCoordInfo();

#pragma region void setTextureOffset(glm::vec2& offset, int index);
	/// Converts the index values in updateTextureCoordInfo to actual offset texture coordinates
	void setTextureOffset(glm::vec2 &offset, int index);
#pragma endregion


#pragma region bool update(Camera* camera);
	/// Called every frame, this is meant to update the particle
	bool update(Camera* camera);
#pragma endregion

};

