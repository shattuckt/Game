#pragma once
#include "Entity.h"
#include "DisplayManager.h"

class Mob : public Entity
{
public:
	float currentSpeed;
	float currentTurnSpeed;
	float upwardsSpeed;

	bool isInAir;
	Mob(TexturedModel model, int index, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	void move(GLFWwindow* window, DisplayManager dmManager);
	void jump();
	Mob(void) {};
	~Mob();
};

