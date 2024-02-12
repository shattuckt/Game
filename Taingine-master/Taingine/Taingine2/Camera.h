#pragma once
#include "ICamera.h"
#include "ICamControls.h"

class Camera : public ICamera{
private:
	static float PITCH_SENSITIVITY;
	static float YAW_SENSITIVITY;
	static float MAX_PITCH;

	static float FOV;
	static float NEAR_PLANE;
	static float FAR_PLANE;

	static float Y_OFFSET;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 position;
	glm::vec3 target;

	ICamControls controls;
	//Window window;
};

