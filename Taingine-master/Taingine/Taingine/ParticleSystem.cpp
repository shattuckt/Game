#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ParticleTexture* texture, float pps, float speed, float gravityComplient, float lifeLength, float scale, DisplayManager* display) {
	this->texture = texture;
	this->pps = pps;
	this->averageSpeed = speed;
	this->gravityComplient = gravityComplient;
	this->averageLifeLength = lifeLength;
	this->averageScale = scale;
	this->display = display;

}

void ParticleSystem::setDirection(glm::vec3 direction, float deviation) {
	this->direction = direction;
	this->directionDeviation = deviation * M_PI;
}
void ParticleSystem::randomizeRotation() {
	this->randomRotation = true;
}
void ParticleSystem::setSpeedError(float error) {
	this->speedError = error * averageSpeed;
}
void ParticleSystem::setLifeError(float error) {
	this->lifeError = error * averageLifeLength;
}
void ParticleSystem::setScaleError(float error) {
	this->scaleError = error * averageScale;
}
void ParticleSystem::generateParticles(std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap> & particles, std::vector<Particle*>& deadParticles, glm::vec3 systemCenter) {
	float delta = display->getFrameTimeSeconds();
	float particlesToCreate = pps * delta;
	int count = floor(particlesToCreate);
	for (int i = 0; i < count; i++) {
		particles[texture].push_back(createParticle(systemCenter, deadParticles));
	}
	//std::cout << "particlesSize for this texture's list: " << particles[texture].size() << std::endl;
	//std::cout << "Printing particles map in the generateParticles method " << std::endl;
	//for (auto const& pair : particles) {
	//	std::cout << "{" << pair.first << ": " << std::endl;
	//	for (int i = 0; i < pair.second.size(); i++) {
	//		std::cout << "Element" << i << " = " << pair.second[i]->getTexture() << std::endl;
	//	}
	//}
}
Particle* ParticleSystem::createParticle(glm::vec3 center, std::vector<Particle*>& deadParticles){
	glm::vec3 velocity;
	if (direction != glm::vec3(0, 0, 0)) {
		velocity = generateRandomUniteVectorWithinCone(direction, directionDeviation);
	}
	else {
		velocity = generateRandomUnitVector();
	}
	
	velocity = glm::normalize(velocity);
	velocity = velocity * generateValue(averageSpeed, speedError);
	float scale = generateValue(averageScale, scaleError);
	float lifeLength = generateValue(averageLifeLength, lifeError);
	
	//std::cout << "velocity = " << velocity.x << "/" << velocity.y << "/" << velocity.z << std::endl;
	count += 1;
	if (deadParticles.size() > 0) {
		deadParticles[0]->setActive(texture, center, velocity, gravityComplient, lifeLength, generateRotation(), scale);
		Particle* p = deadParticles[0];
		deadParticles.erase(deadParticles.begin());
		return p;
	}
	else {
		//if (count % 1000 == 0) {
			//std::cout << "creating new - count: " << count << std::endl;
		//}
		return new Particle(texture, center, velocity, gravityComplient, lifeLength, generateRotation(), scale, this->display);
	}
	
}
float ParticleSystem::generateValue(float average, float errorMargin) {
	float offset = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * - 0.5f) * 2.0f * errorMargin;
	return average + offset;
}
float ParticleSystem::generateRotation() {
	if (randomRotation) {
		return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 360.0f;
	}
	else {
		return 0;
	}
}
glm::vec3 ParticleSystem::generateRandomUniteVectorWithinCone(glm::vec3 coneDirection, float angle) {
	float cosAngle = cos(angle);
	float theta = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2.0f * M_PI;
	float z = cosAngle + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))* (1 - cosAngle);
	float rootOneMinusZSquared = sqrt(1 - z * z);
	float x = rootOneMinusZSquared * cos(theta);
	float y = rootOneMinusZSquared * sin(theta);

	//std::cout << "cosAngle = " << cosAngle << "\n theta = " << theta << "\n rootOneMinusZSquared = " << rootOneMinusZSquared << std::endl;

	glm::vec4 direction = glm::vec4(x, y, z, 1);
	//std::cout << "Cone direction: " << direction[0] << "/" << direction[1] << "/" << direction[2] << "/" << direction[3] << std::endl;
	if (coneDirection.x != 0 || coneDirection.y != 0 || (coneDirection.z != 1 && coneDirection.z != -1)) {
		glm::vec3 rotateAxis = coneDirection * glm::vec3(0, 0, 1);
		//std::cout << "rotateAxis " << rotateAxis[0] << "/" << rotateAxis[1] << "/" << rotateAxis[2] << std::endl;
		rotateAxis = glm::normalize(rotateAxis);
		float rotateAngle = acos(glm::radians(glm::dot(coneDirection, glm::vec3(0, 0, 1))));
		glm::mat4 rotationMatrix;
		rotationMatrix = glm::rotate(rotationMatrix, -rotateAngle, rotateAxis);
		direction = rotationMatrix * direction;
	}
	else if (coneDirection.z == 1) {
		direction.z *= -1;
	}
	//0, 0, 1
	
	return direction;
}
glm::vec3 ParticleSystem::generateRandomUnitVector() {
	float theta = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2.0f * M_PI;

	float z = static_cast <float> (Utility::RandDouble(-1, 1));

	float rootOneMinusZSquared = sqrt(1 - z * z);
	float x = rootOneMinusZSquared * cos(theta);
	float y = rootOneMinusZSquared * sin(theta);

	return glm::vec3(x, y, z);
}