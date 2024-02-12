#pragma once
#include "ParticleRenderer.h"
#include "ParticleSystem.h"
#include "TaingineThreads.h"
#include <thread>




class ParticleMaster
{
private:
	//std::vector<Particle*> particles;
	std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap> particles;
	std::vector<Particle*> deadParticles;

	ParticleRenderer* renderer;

public:
	ParticleMaster(Loader loader, glm::mat4 projectionMatrix);
	
	void update(Camera* camera);

	void generateParticles(ParticleSystem* system, glm::vec3 position);

	void renderParticles(Camera* camera);

	void cleanUp();

	void addParticle(Particle* particle);

	void insertionSort(vector<Particle*>& particles);
};

