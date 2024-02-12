#include "ParticleMaster.h"

ParticleMaster::ParticleMaster(Loader loader, glm::mat4 projectionMatrix) {
	this->renderer = new ParticleRenderer(loader, projectionMatrix);
}

void ParticleMaster::update(Camera* camera) {

	for (std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap>::iterator it = particles.begin(); it != particles.end(); ++it) {
		//std::vector<Particle*> particleList = it->second;
		std::vector<Particle*>::iterator partListIt = it->second.begin();
		while (partListIt != it->second.end()) {
			//std::cout << "particles.size when updating = " << it->second.size() << std::endl;
			Particle* p = *partListIt;
			bool stillAlive = p->update(camera);
			if (!stillAlive) {
				//deadParticles.push_back(p);
				partListIt = it->second.erase(partListIt);
				if (it->second.size() == 0) {
					//std::cout << "particles.size after updating = " << it->second.size() << std::endl;
					//std::cout << "map list size = " << it->second.size() << std::endl;
					break;
				}

			}
			else {
				++partListIt;
			}

		}
		if( !it->first->usesAdditiveBlending()){
		//	std::thread* threadObj = new std::thread(&ParticleMaster::insertionSort, this, std::ref(it->second));
		//	TaingineThreads::taingineThreads["particleThread"] = threadObj;
			insertionSort(std::ref(it->second));
		}
	}


	

}

void ParticleMaster::generateParticles(ParticleSystem* system, glm::vec3 position) {
	system->generateParticles(particles, deadParticles, position);
}

void ParticleMaster::renderParticles(Camera* camera) {
	renderer->render(particles, camera);
}

void ParticleMaster::cleanUp() {
	renderer->cleanUp();
}

void ParticleMaster::addParticle(Particle* particle) {
	//particles.push_back(particle);
	particles[particle->getTexture()].push_back(particle);

	std::cout << "Printing particles map in the addParticleMethod " << std::endl;
	for (auto const& pair : particles) {
		std::cout << "{" << pair.first << ": " << std::endl;
		for (int i = 0; i < pair.second.size(); i++) {
			std::cout << "Element" << i << " = " << pair.second[i] << std::endl;
		}
	}
}

void ParticleMaster::insertionSort(vector<Particle*>& particles) {
	unsigned int i, j;
	vector<Particle*> sortedArray(particles.size());
	float max;
	Particle* particleHolder;

	//for (i = 0; i < particles.size(); i++) {
	//	particleHolder = particles[i];

	//	for (j = i; j < particles.size(); j++) {
			//particleHolder = particles[j]->getDistance() <= particleHolder->getDistance() ? particles[j] : particleHolder;
	//	}

	//	sortedArray[i] = particleHolder;
	//}
	//particles = sortedArray;
	//std::cout << "Size of particles vector : " << particles.size() << std::endl;
	for (int k = 1; k < particles.size(); k++) {
		//std::cout << "looking at element " << k << " of the sort..." << std::endl;
		Particle* temp = particles[k];
		int j = k - 1;
		while (j >= 0 && temp->getDistance() >= particles[j]->getDistance()) {
			particles[j + 1] = particles[j];
			j = j - 1;
		}
		particles[j + 1] = temp;
	}

	//particles = sortedArray;
	//std::cout << "particles size = " << particles.size() << std::endl;
	//std::cout << "********************************************************************************************** " << std::endl;
	//print the sorted vector:
	//********************************************************************************
	//std::cout << "stop fool" << std::endl;
}