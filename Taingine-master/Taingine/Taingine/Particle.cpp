#include "Particle.h"

const float GRAVITY = -50;

Particle::Particle(ParticleTexture* texture, glm::vec3 position, glm::vec3 velocity, float gravityEffect,
	float lifeLength, float rotation, float scale, DisplayManager* display) {

	this->position = position;
	this->velocity = velocity;
	this->gravityEffect = gravityEffect;
	this->lifeLength = lifeLength;
	this->rotation = rotation;
	this->scale = scale;
	this->texture = texture;

	this->display = display;

	//ParticleMaster.addParticle(this);

}

void Particle::setActive(ParticleTexture* texture, glm::vec3 position, glm::vec3 velocity, float gravityEffect,
	float lifeLength, float roation, float scale) {
	this->position = position;
	this->velocity = velocity;
	this->gravityEffect = gravityEffect;
	this->lifeLength = lifeLength;
	this->rotation = rotation;
	this->scale = scale;
	this->texture = texture;
	this->elapsedTime = 0;
}

ParticleTexture* Particle::getTexture() {
	return this->texture;
}
glm::vec3 Particle::getPosition() {
	return this->position;
}

float Particle::getRotation() {
	return this->rotation;
}

float Particle::getScale() {
	return this->scale;
}

glm::vec2 Particle::getTexOffset1() {
	return this->texOffset1;
}

glm::vec2 Particle::getTexOffset2() {
	return this->texOffset2;
}

float Particle::getBlend() {
	return this->blend;
}

float Particle::getDistance() {
	return this->distance;
}

void Particle::updateTextureCoordInfo() {
	float lifeFactor = elapsedTime / lifeLength;
	int stageCount = this->texture->getNumberOfRows() * this->texture->getNumberOfRows();
	float atlasProgression = lifeFactor * stageCount; //this is how far along the atlas we have gotten. 
	int index1 = floor(atlasProgression);
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;

	float intPart;
	this->blend = modf(atlasProgression, &intPart);

	setTextureOffset(texOffset1, index1);
	setTextureOffset(texOffset2, index2);

}

void Particle::setTextureOffset(glm::vec2 &offset, int index) {
	int column = index % texture->getNumberOfRows();
	int row = index / texture->getNumberOfRows();
	offset.x = (float) column / texture->getNumberOfRows();
	offset.y = (float) row / texture->getNumberOfRows();
}

bool Particle::update(Camera* camera) {
	velocity.y += GRAVITY * gravityEffect * display->getFrameTimeSeconds();
	change = velocity;
	change = change * display->getFrameTimeSeconds(); //how much should the velocity change this frame

	//std::cout << "Position before change add: \n " << position.x << "/" << position.y << "/" << position.z << std::endl;
	position += change;
	//std::cout << "Position after change add: \n " << position.x << "/" << position.y << "/" << position.z << std::endl;

	//distance = sqrt(pow((camera->getCameraPosition().x - position.x), 2) + pow((camera->getCameraPosition().y - position.y), 2) + pow((camera->getCameraPosition().z - position.z), 2)); //there has to a better way of doing this
	distance = pow((camera->getCameraPosition().x - position.x), 2) + pow((camera->getCameraPosition().y - position.y), 2) + pow((camera->getCameraPosition().z - position.z), 2);

	updateTextureCoordInfo();

	elapsedTime += display->getFrameTimeSeconds();


	//std::cout << "Elapsed time = " << elapsedTime << std::endl;

	return elapsedTime < lifeLength;
}