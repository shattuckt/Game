#pragma once
//#include <glm-0.9.8.5\glm\glm.hpp>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "Player.h"

class Player;

class Camera
{
private:

	Player * player; //Players *players;
	DisplayManager* display;
	GLFWwindow* window;

	float distanceFromPlayer;
	float angleAroundPlayer;

	glm::vec3 cameraPosition;
	float pitch;
	float yaw;
	float roll;

	bool firstMouse;
	float lastX;
	float lastY;

	bool cursor;

	glm::mat4 viewMatrix;


public:
	Camera(GLFWwindow* window, DisplayManager* display, Player* player);
	Camera(void) {};
	~Camera(void);

	void move();

	void calculateCameraPosition(float horizDistance, float verticDistance);
	float calculateHorizontalDistance();
	float calculateVerticalDistance();

	void invertPitch();
	glm::vec3 getCameraPosition();
	float getPitch();
	float getYaw();
	float getRoll();
	float getAngleAroundPlayer();

	void setPitch(float pitchs);
	void setYaw(float yaws);
	void setRoll(float rolls);
	void setCameraPosition(glm::vec3 cameraPositions);


	void mouse_handler(double xpos, double ypos); //trying to handle the mouse input...
	void scroll_handler(double xoffset, double yoffset); //trying to handle the mouse scroll input... 
	void button_handler(int button, int action, int mods);

	void createViewMatrix();

	glm::mat4 getViewMatrix();

};

