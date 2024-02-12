#include "MousePicker.h"

void picker_mouse_callback(GLFWwindow *window, double xpos, double ypos); //tracks mouse movement 

MousePicker::MousePicker(GLFWwindow* windows, Camera* cam, glm::mat4 projection, Player* players, DisplayManager* displays) {

	camera = cam; //copy camera object... 
	player = players;
	display = displays;
	window = windows; //copy window object..
	projectionMatrix = projection;
	viewMatrix = camera->getViewMatrix();
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, picker_mouse_callback); //required in order for glfw to know which callback to use for the mouse
}


glm::vec3 MousePicker::getWorldRay() {
	return worldRay;
}

void MousePicker::update() {

	if (player->getCursorOn() == true) { //the window pointer must be set in the class its being used in
		glfwSetWindowUserPointer(window, this); //required to access functions inside of this class for the callbacks 
		glfwSetCursorPosCallback(window, picker_mouse_callback); //required in order for glfw to know which callback to use for the mouse
		cursor = true;
	}
	else {
		cursor = false;
	}
	viewMatrix = camera->getViewMatrix(); //at the moment, this has to be created each frame since the yaw and stuff will change... 
}

glm::vec3 MousePicker::calculateMouseRay() {
	return glm::vec3(0, 0, 0);
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords) {
	glm::mat4 invertedView = glm::inverse(viewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords; //transform the eye coords into world coords by transforming with the invertedView 
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = glm::normalize(mouseRay); //ensure the coordinates are w/in 1 
	return mouseRay;
}

//Tthe following functions transforms the prjection tranformed 
glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords) {
	glm::mat4 invertedProjection = glm::inverse(projectionMatrix); //invert the projection matrix
	glm::vec4 eyeCoords = invertedProjection * clipCoords; //transform the clip coords into eye coords by transforming it with the invertedProjection 
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}
//The following finds the (x,y) coordinate of OpenGL on the screen from the mouse coordinates. The grid is -1 to 1, so we must multiply the value by 2 and then subtract 1... 
glm::vec2 MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY) {
	float x = (2.0f * mouseX) / display->getWidth() - 1;
	float y = (2.0f * mouseY) / display->getHeight() - 1;
	return glm::vec2(x, y);
}

/*//**********************************************************************
In order to handle cursor movement, the code below is used. First the top function, mouse_callback, directly handles all movement immediately when the mouse is moved by the user
However, since this function must be isolated inside the class its placed in. A second function, mouse_handler, must be called to actually
perform actions on the mouse movement.. */
void picker_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	void *data = glfwGetWindowUserPointer(window); //obtain the pointer attribute - this allows us to access functions without having to create a new object
	MousePicker *picker = static_cast<MousePicker *>(data); //use a pointer to access the camera class
	picker->mouse_handler(window, xpos, ypos); //then use the obtained access to call the mouse_handler (below)
}

void MousePicker::mouse_handler(GLFWwindow* window, double xpos, double ypos) {
	if (cursor == true) { //If the cursor is active and not clamped to the screen... 
		//std::cout << "MousePicker activated..." << std::endl;

		//Convert the mouse coordinates into a world space 3d ray
		//****Starting in VIEWPORT SPACE
		glm::vec2 normalizedCoords = getNormalizedDeviceCoords(xpos, ypos); //convert the mouse coordinates to openGL coordinates on screen (between -1 and 1 for both values)
																			//****we are now in NORMALIZED DEVICE SPACE (so the below line needs the inverse perspective applied to it in order to go to the homogenous clip space
		glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f); //we dont need to inverse the perspecive point since we just want a 3d vector and not a 3d point
																							   //****we are now in HOMOEGENEOUS CLIP SPACE (so the below line needs the PROJECTION matrix INVERSE applied to it in order to move into eye space 
		glm::vec4 eyeCoords = toEyeCoords(clipCoords); //apply inverse projection matrix 
													   //****we are now in EYE SPACE (so the below line needs the VIEW matrix INVERSE applied to it in order to move into world space (the final step) 
		worldRay = toWorldCoords(eyeCoords); //apply the inverse view matrix

		//std::cout << "The mousePicker was updated - X: " << worldRay.x << " Y: " << worldRay.y << " Z: " << worldRay.z << std::endl;
	}
}

MousePicker::~MousePicker(void) {
}
