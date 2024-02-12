#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <glm-0.9.8.5/glm/glm.hpp>
#include <glm-0.9.8.5\glm\gtc\matrix_transform.hpp>
#include "ParticleRenderer.h"
#include "Utility.h"

class ParticleSystem
{
private:
	float pps, averageSpeed, gravityComplient, averageLifeLength, averageScale;

	float speedError, lifeError, scaleError = 0;
	bool randomRotation = false;
	glm::vec3 direction = glm::vec3(0,0,0);
	float directionDeviation;

	ParticleTexture* texture;

	DisplayManager* display;

	int count = 0;

public:
#pragma region ParticleSystem(ParticleTexture* texture, float pps, float speed, float gravityComplient, float lifeLength, float scale, DisplayManager* display);
	/// Velocity being a vector dictating the speedand direction it is traveling.
	///	gravityEffect is how much that particle is effected by gravity, closer to zero means less gravity
	///	lifeLength is the duration of the particle's life
	ParticleSystem(ParticleTexture* texture, float pps, float speed, float gravityComplient, float lifeLength, float scale, DisplayManager* display);
#pragma endregion

#pragma region setDirection(glm::vec3 direction, float deviation);
	/// Direction - average direction in which particles are emitted
	/// deviation - a value between 0 and 1 indicating how far from the chosen direction particles can deviate.
	void setDirection(glm::vec3 direction, float deviation);
#pragma endregion

	void randomizeRotation();

#pragma region setSpeedError(float error);
	/// Error - - A number between 0 and 1, where 0 means no error margin.
	void setSpeedError(float error);
#pragma endregion

#pragma region setLifeError(float error);
	/// Error - - A number between 0 and 1, where 0 means no error margin.
	void setLifeError(float error);
#pragma endregion

#pragma region setScaleError(float error);
	/// Error - - A number between 0 and 1, where 0 means no error margin.
	void setScaleError(float error);
#pragma endregion

	void generateParticles(std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap> & particles, std::vector<Particle*>& deadParticles, glm::vec3 systemCenter);

	Particle* createParticle(glm::vec3 center, std::vector<Particle*>& deadParticles);
	float generateValue(float average, float errorMargin);
	float generateRotation();
	glm::vec3 generateRandomUniteVectorWithinCone(glm::vec3 coneDirection, float angle);
	glm::vec3 generateRandomUnitVector();

};

