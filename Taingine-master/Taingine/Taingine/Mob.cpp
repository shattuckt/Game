#include "Mob.h"

//These will probably need to be dynamic for faster or slower mobs... 
const int RUN_SPEED = 20;
const int TURN_SPEED = 50;
const float GRAVITY = -50;
const float JUMP_POWER = 30;

const float TERRAIN_HEIGHT = 0; //right now the terrain is static so... Y = 0

Mob::Mob(TexturedModel model, int index, glm::vec3 position, float rotX, float rotY, float rotZ, float scale) {
	this->textureIndex = index;
	this->model = model;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	currentSpeed = 0; // start player speed at zero
	currentTurnSpeed = 0; // start player rotation at zero 
	upwardsSpeed = 0; //used for the jump method
	isInAir = false; //this prevents the player from jumping once already in the air 
}

void Mob::move(GLFWwindow* window, DisplayManager dmManager) {



	//******************simply boilerplate code right now... 

	//std::cout << "the position of player (inside player.cpp) is (" << getPosition().x << ", " << getPosition().y << ", " << getPosition().z << std::endl;
	//std::cout << "The current speed is " << dmManager.getFrameTimeSeconds() << std::endl;
	increaseRotation(0, currentTurnSpeed * dmManager.getFrameTimeSeconds(), 0);
	float distance = currentSpeed * dmManager.getFrameTimeSeconds();
	//std::cout << "rotY is " << getRotY() << std::endl;
	//std::cout << "dx is equal to " << distance << " * " << sin(glm::radians(getRotY())) << " = " << distance * sin(glm::radians(getRotY())) << std::endl;
	//std::cout << "dy is equal to " << distance << " * " << cos(glm::radians(getRotY())) << " = " << distance * cos(glm::radians(getRotY())) << std::endl;

	float dx = distance * sin(glm::radians(getRotY()));
	float dz = distance * cos(glm::radians(getRotY()));
	increasePosition(dx, 0, dz);
	upwardsSpeed += GRAVITY * dmManager.getFrameTimeSeconds();
	increasePosition(0, upwardsSpeed * dmManager.getFrameTimeSeconds(), 0);
	if (getPosition().y < TERRAIN_HEIGHT) {
		upwardsSpeed = 0;
		isInAir = false;
		setPosition(glm::vec3(getPosition().x, TERRAIN_HEIGHT, getPosition().z));
	}
	//**********************************
}

void Mob::jump() {
	if (!isInAir) {
		upwardsSpeed = JUMP_POWER;
		isInAir = true;
	}
}

Mob::~Mob()
{
}
