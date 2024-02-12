#pragma once
#include <glm-0.9.8.5\glm\glm.hpp>
#include "Camera.h"
class MousePicker
{
private:

	bool cursor;
	glm::vec3 worldRay;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Camera* camera;
	Player* player;
	DisplayManager* display;

	GLFWwindow* window;

public:
	MousePicker(GLFWwindow* windows, Camera* cam, glm::mat4 projection, Player* players, DisplayManager* displays);

	glm::vec3 getWorldRay();
	void update();
	glm::vec3 calculateMouseRay();

	glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
	glm::vec4 toEyeCoords(glm::vec4 clipCoords);
	glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);


	void mouse_handler(GLFWwindow* window, double xpos, double ypos);

	~MousePicker(void);
};

