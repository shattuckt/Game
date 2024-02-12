#pragma once
#include "Entity.h"
#include "DisplayManager.h"
#include "Terrain.h"
#include "Camera.h"

class Camera;

class Player : public Entity {
private:
	float currentSpeed; //current speed of player 
	float currentTurnSpeed; //current turn speed of player 
	float currentStrafeSpeed; //current strafe speed of player
	float upwardsSpeed; //this is used for the jump method

	int coolDownTimer; //This will use the internal clock we made to simulate a cooldown 
	bool keyDown;

	bool isInAir;
	bool cursorOn;

	GLFWwindow* window;
	DisplayManager* display;
	Camera* camera;


public:
	Player(TexturedModel model, int index, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, GLFWwindow* window);
	Player(void) {};
	void move(float angle, float terrainHeight);
	void setCamera(Camera* camera);
	void setDisplay(DisplayManager* display);
	void jump();
	void checkInputs();
	void player_key_callback_handler(int key, int scancode, int action, int mods);
	void toggleCursor();
	bool getCursorOn();
	~Player(void);
};

