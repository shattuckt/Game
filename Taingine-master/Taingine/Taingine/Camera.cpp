#include "Camera.h"

void mouse_callback(GLFWwindow *window, double xpos, double ypos); //tracks mouse movement 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); //captures scroll wheel. NOTE: WILL NEED TO BE MOVED TO PLAYER for tool bar. 
void button_callback(GLFWwindow* window, int button, int action, int mods);

Camera::Camera(GLFWwindow* window, DisplayManager* display, Player* player)
{
	this->player = player;
	this->display = display;
	this->window = window;

	//glfwSetWindowUserPointer(windows, this);

	/*glfwSetCursorPosCallback(window, mouse_callback);*/
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetMouseButtonCallback(window, button_callback);



	this->distanceFromPlayer = 10;
	this->angleAroundPlayer = 180; //this changes the starting view of the player.. so if you want to rotate the view to the rear, then set this to 180. 0 makes it where the character is looking towards the positive Z axis. 

	this->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->yaw = 0.0f;
	this->pitch = 5.2f; //this is the same for both the player and the camera.
	this->firstMouse = true;
	this->lastX = 0;
	this->lastY = 0;

	createViewMatrix();

}

Camera::~Camera(void) {}

void Camera::move() {


	float horizontalDistance = calculateHorizontalDistance();
	float verticalDistance = calculateVerticalDistance();

	calculateCameraPosition(horizontalDistance, verticalDistance);
	player->setRotY(angleAroundPlayer); //player->setRotY(angleAroungPlayer);
	yaw = 90 - (angleAroundPlayer); //this orientates the camera around the player. 90 keeps it directly behind the character. 

}


void Camera::calculateCameraPosition(float horizDistance, float verticDistance) {
	//std::cout << "the position of player (inside camera.cpp) is (" << player.getPosition().x << ", " << player.getPosition().y << ", " << player.getPosition().z << std::endl;

	//std::cout << "theta is " << player.getRotY() << " + " << angleAroundPlayer << " = " << player.getRotY() + angleAroundPlayer << std::endl;

	//The following will move the camera back from the player. 3rd person.... 
	float theta = player->getRotY();
	float offsetX = (float)(horizDistance * sin(glm::radians(theta)));
	float offsetZ = (float)(horizDistance * cos(glm::radians(theta)));
	cameraPosition.x = player->getPosition().x - offsetX;
	cameraPosition.z = player->getPosition().z - offsetZ;
	cameraPosition.y = player->getPosition().y + verticDistance + 5;
	//Instead, we want to implement a camera that is inside the player's head 
	//cameraPosition.x = player->getPosition().x; //this will always be the same as the player... 
	//cameraPosition.z = player->getPosition().z; //this will also always be the same as the player... 
	//cameraPosition.y = player->getPosition().y + 10.5; //however, this will need a value added to it based on the height of the player entity  ATTEMPT ONCE COLLISSION DETECTION IS IMPLEMENETED (DIMENSIONS WILL BE KNOWN THEN

	if (player->getCursorOn() == false) { //the window pointer must be set in the class its being used in
		glfwSetWindowUserPointer(window, this); //required to access functions inside of this class form the callbacks 
		glfwSetCursorPosCallback(window, mouse_callback);
		cursor = false;
	}
	else {
		cursor = true;
	}
	//std::cout << "the lastX is " << lastX << " and the lastY is " << lastY << std::endl;
	//std::cout << "The x cameraposition is derives from player.getPosition().x) - offsetX : " << player.getPosition().x << " - " << offsetX << " = " << player.getPosition().x - offsetX << std::endl;
	//std::cout << "The z cameraPosition is derived from player.getPosition().y - offsetZ : " << player.getPosition().y << " - " << offsetZ << " = " << player.getPosition().z - offsetZ << std::endl;
	//std::cout << "The Y cameraPosition is derived from player.getPosition().y - verrticDistance " << player.getPosition().y << " + " << verticDistance << " = " << player.getPosition().y + verticDistance << std::endl;
}

float Camera::calculateHorizontalDistance() { //THis gives the distance between the camera and the player 

											  //so if it starts at 50. and the pitch is 20...
											  //std::cout << "The following should be.. 50 * 0.93969 ...." << distanceFromPlayer << " and " << cos(pitch) << std::endl;
											  //std::cout << "so... the horizontal distance would be " << distanceFromPlayer * cos(pitch) << std::endl;
	return (float)distanceFromPlayer;// *cos(glm::radians(pitch));
}
float Camera::calculateVerticalDistance() {
	//std::cout << "verticDistance: "  << distanceFromPlayer << " and " << sin(glm::radians(pitch)) << "together : " << (float)distanceFromPlayer * sin(glm::radians(pitch)) << std::endl;
	return (float)distanceFromPlayer;// *sin(glm::radians(pitch));

}

void Camera::invertPitch() {
	pitch = -pitch;
}
glm::vec3 Camera::getCameraPosition() {
	return cameraPosition;
}
float Camera::getPitch() {
	return pitch;
}
float Camera::getYaw() {
	return yaw;
}
float Camera::getRoll() {
	return roll;
}

float Camera::getAngleAroundPlayer() {
	return angleAroundPlayer;
}

void Camera::setPitch(float pitchs) {
	pitch = pitchs;
}
void Camera::setYaw(float yaws) {
	yaw = yaws;
}
void Camera::setRoll(float rolls) {
	roll = rolls;
}
void Camera::setCameraPosition(glm::vec3 cameraPositions) {
	cameraPosition = cameraPositions;
}

//The viewMatrix is moving all the objects to the opposite direction you are pointing towards. this gives the illusion you are moving.
//Note: this doesnt use "Roll" because it wasnt used in the tutorial.
void Camera::createViewMatrix() {

	glm::mat4 viewMatrix;
	glm::vec3 cameraPos = getCameraPosition();
	glm::vec3 cameraFront; // = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 front;
	front.x = cos(glm::radians(getPitch())) * cos(glm::radians(getYaw()));
	front.y = sin(glm::radians(getPitch()));
	front.z = cos(glm::radians(getPitch())) * sin(glm::radians(getYaw()));
	cameraFront = glm::normalize(front); //depicts how high or low the camera is looking 
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	this->viewMatrix = viewMatrix;
}

glm::mat4 Camera::getViewMatrix() {
	return this->viewMatrix;
}

//*************************THe below code is for the mouse curser. it currently is not being used. 
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	void *data = glfwGetWindowUserPointer(window); //obtain the pointer attribute - this allows us to access functions without having to create a new object
	Camera *cam = static_cast<Camera *>(data); //use a pointer to access the camera class
	cam->mouse_handler(xpos, ypos); //then use the obtained access to call the mouse_handler (below)
}

void Camera::mouse_handler(double xpos, double ypos) {
	if (cursor == false) {
		if (firstMouse == 1) {
			std::cout << "inside mouse_handler (second), the lastX and lastY are being set to " << xpos << " and " << ypos << ", respectively." << std::endl;
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		//std::cout << "the xoffset is " << xpos << " - " << lastX << " = " << xpos - lastX << std::endl;
		//std::cout << "the yoffset is " << lastY << " - " << ypos << " = " << lastY - ypos << std::endl;
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
									  //std::cout << "LastX is being set to " << xpos << std::endl;
									  //std::cout << "LastY is being set to " << ypos << std::endl;
		lastX = xpos;
		lastY = ypos;

		//std::cout << "Offsets are : x: " << xoffset << " and y: " << yoffset << std::endl;
		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity; //You can always add a decimal value to make one of the directions slightly quicker... but right now they are the same
		yoffset *= sensitivity;

		//std::cout << "final xoffset " << xoffset << std::endl;

		angleAroundPlayer -= xoffset;
		pitch += yoffset;

		//ensure the pitch never gets lower or higher than 89 degrees... 
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		//Ensure angle stays in 360 degree range. 
		angleAroundPlayer = (int)angleAroundPlayer % 360; //have to convert to int... not the best
	}

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { //This must exist for the scroll wheel to do anything 
	void *data = glfwGetWindowUserPointer(window);
	Camera *cam = static_cast<Camera *>(data);
	cam->scroll_handler(xoffset, yoffset); //we then use pointers in order to access the camera object and then use our implementation class 
}

void Camera::scroll_handler(double xoffset, double yoffset) { //This is the actual implementation of the scroll wheel action 
	float zoomLevel = yoffset * 2;
	std::cout << "Distance from player increasing - its current value: " << distanceFromPlayer << std::endl;
	distanceFromPlayer -= zoomLevel; //Whenever the user spins the mousewheel down, the distance from player will increase.
}

void button_callback(GLFWwindow* window, int button, int action, int mods) { //THis must exist for the mouse button to do anything 
	void *data = glfwGetWindowUserPointer(window);
	Camera *cam = static_cast<Camera *>(data);
	cam->button_handler(button, action, mods); //We again use fancy pointers to access the camera object and then use our implementation class 
}

void Camera::button_handler(int button, int action, int mods) { //This is the actual implmentation of the mouse button action 


																/*
																if (button == 1 && action == 1) { //if the player has pressed the right mouse button  (we want to increase the angle of pitch)
																float pitchChange = -4.0f;
																float totalPitch = pitchChange + pitch;
																if (totalPitch > 89.0f)
																totalPitch = 89.0f;
																else if (totalPitch < 0.0f)
																totalPitch = 0.0f;
																//pitch = totalPitch; //so if you right click, the camera will move closer to the ground
																}
																if (button == 0 && action == 1) { //if the player has pressed the left button (we want to rotate our view of the player) this is independent of where the player is going
																float angleChange = 10.0f;
																float totalAngle = angleChange + angleAroundPlayer;
																if (angleAroundPlayer > 360)
																totalAngle = totalAngle - 360;
																//angleAroundPlayer = totalAngle;
																}*/
}
