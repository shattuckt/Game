#include "Player.h"

const int RUN_SPEED = 60;
const int TURN_SPEED = 50;
const float GRAVITY = -50;
const float JUMP_POWER = 30;
const int coolDown = 10;


								//void player_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Player::Player(TexturedModel model, int index, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, GLFWwindow* window) {
	this->textureIndex = index;
	this->model = model;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	this->window = window;
	this->display = new DisplayManager();
	this->camera = new Camera();
	currentSpeed = 0; // start player speed at zero
	currentStrafeSpeed = 0;
	currentTurnSpeed = 0; // start player rotation at zero 
	upwardsSpeed = 0; //used for the jump method
	coolDownTimer = 0; //Used for the input delay
	isInAir = false; //this prevents the player from jumping once already in the air 
	this->cursorOn = false;
}

void Player::move(float angle, float terrainHeight) {
	//std::cout << "the position of player (inside player.cpp) is (" << getPosition().x << ", " << getPosition().y << ", " << getPosition().z << std::endl;
	if (cursorOn == false) { //the window pointer must be set in the class its being used in
							 //glfwSetWindowUserPointer(window, this); //required to access functions inside of this class form the callbacks 
							 //glfwSetKeyCallback(window, player_key_callback);
	}

	checkInputs();
	//angle = abs(angle);
	//DisplayManager dmManager;
	increaseRotation(0, currentTurnSpeed * display->getFrameTimeSeconds(), 0);
	float distance = currentSpeed * display->getFrameTimeSeconds();
	float strafeDistance = currentStrafeSpeed * display->getFrameTimeSeconds();

	float dx = distance *sin(glm::radians(angle));
	float dz = distance *cos(glm::radians(angle));
	float strafeX = -strafeDistance *sin(glm::radians(angle - 90));
	float strafeZ = -strafeDistance *cos(glm::radians(angle - 90));
	
	//std::cout << "The increasePosition parameters moving side to side are as follows: " <<
		//" X: " << dx + strafeX << " Y: 0 Z: " << dz + strafeZ << std::endl;
	increasePosition(dx + strafeX, 0, dz + strafeZ); //This allows for the forward and strafe keys being held at the same time... 
	upwardsSpeed += GRAVITY * display->getFrameTimeSeconds();
	increasePosition(0, upwardsSpeed * display->getFrameTimeSeconds(), 0);

	if (getPosition().y < terrainHeight) {
		upwardsSpeed = 0;
		isInAir = false;
		setPosition(glm::vec3(getPosition().x, terrainHeight, getPosition().z));
	}

}

void Player::setCamera(Camera* camera) {
	this->camera = camera;
}
void Player::setDisplay(DisplayManager* display) {
	this->display = display;
}

void Player::jump() {
	if (true) { //if (!isInAir) { //so we can 'fly'...
		upwardsSpeed = JUMP_POWER;
		isInAir = true;
	}
}

void Player::checkInputs() {


	if (cursorOn == false) { //So if the player has decided to close the menu (or just default), then do normal player controls... 
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			currentSpeed = RUN_SPEED;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			currentSpeed = -RUN_SPEED;
		}
		else
			currentSpeed = 0;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			//currentTurnSpeed = -TURN_SPEED; //this turns the player - it is not a strafe 
			currentStrafeSpeed = -RUN_SPEED;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			//currentTurnSpeed = TURN_SPEED; //this turns the player - it is not a strafe 
			currentStrafeSpeed = RUN_SPEED;
		}
		else
			//currentTurnSpeed = 0;
			currentStrafeSpeed = 0;

		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			jump();
			//checkInputs(window);
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			//dodge roll...
		}


		//************************ Input requiring cooldown ***********************
		if (coolDownTimer <= 0) {
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				coolDownTimer = coolDown; //start the cooldown 
				toggleCursor(); //Activate the menu 
			}

		}
		else {
			coolDownTimer = coolDownTimer - 1;
		}


	}
	//**************************** Menu Input **************************************
	else if (cursorOn == true) { //activate the menu 

								 //*************************Menu Input requiring cooldown ********************
		if (coolDownTimer <= 0) {
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				coolDownTimer = coolDown; //start the cooldown 
				toggleCursor(); //Deactivate the menu 
			}
		}
		else {
			coolDownTimer = coolDownTimer - 1;
		}
	}


}

/*void player_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	void *data = glfwGetWindowUserPointer(window);
	Player* player = static_cast<Player*>(data);
	player->player_key_callback_handler(key, scancode, action, mods); //we then use pointers in order to access the camera object and then use our implementation class 
}
void Player::player_key_callback_handler(int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		currentSpeed = RUN_SPEED;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		currentSpeed = -RUN_SPEED;
	}
	else
		currentSpeed = 0;

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		currentStrafeSpeed = -RUN_SPEED;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		currentStrafeSpeed = RUN_SPEED;
	}
	else
		currentStrafeSpeed = 0;

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		jump();
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		//dodge roll...
	}

	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		toggleCursor();
	}

}*/

void Player::toggleCursor() {  
	std::cout << "Toggle cursor has been called!" << std::endl;
	if (cursorOn == false) { //turn the 'hud' off (hide the cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //This simulates the cursor being bound to the middle of the screen
		cursorOn = true;
	}
	else {//the 'hud' has been turned on, activate cursor 
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //turns the cursor on
		cursorOn = false;
	}

	//Why doesnt this work?
	std::cout << "Pitch is equal to : " << camera->getPitch() << std::endl;
}

bool Player::getCursorOn() {
	/*std::cout << "CursorOn called.. player::getCursorOn " << cursorOn << std::endl;*/
	return cursorOn;
}




Player::~Player(void)
{
}
