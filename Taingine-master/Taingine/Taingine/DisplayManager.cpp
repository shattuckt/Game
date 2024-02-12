#include "DisplayManager.h"

//const int WIDTH = 320; //320   1280;
//const int HEIGHT = 180; //180   720;
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //this thing isnt working. 


DisplayManager::DisplayManager() {
	WIDTH = 1280;
	HEIGHT = 720;
	lastFrameTime = getCurrentTime();
	window = NULL;
}

void DisplayManager::createDisplay() {

	//The following initializes the GLFW library 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //This is meant to make this program compatible with Macs							

	window = glfwCreateWindow(WIDTH, HEIGHT, "Version Alpha 0.3", NULL, NULL);

	if (window == NULL) { //if the window wasnt able to be created...
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window); //Else make the context of our window the main context of the current thread
	//glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //This simulates the cursor being bound to the middle of the screen.

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //if glad failed to load
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, WIDTH, HEIGHT); //render the screen (this one only runs once at the moment...)
	lastFrameTime = getCurrentTime(); //Prepare the update display by obtaining the currentTime for the lastFrame
	delta = 0; //initialize delta so the starting change in time isn't some crazy number 
			   //std::cout << "lastFrame time in the createDisplay method is " << lastFrameTime << std::endl;

}

GLFWwindow* DisplayManager::getWindow() {
	return this->window;
}

void DisplayManager::updateDisplay() {


	//This sets the FPS of the game
	glfwSwapInterval(1);
	glfwSwapBuffers(this->window);

	float currentFrameTime = getCurrentTime();
	//std::cout << "inside display manager, currentFrameTime is " << currentFrameTime << " and lastFrameTime is " << lastFrameTime << std::endl;
	//std::cout << "so delta equals = " << currentFrameTime - lastFrameTime << std::endl;
	delta = currentFrameTime - lastFrameTime; //Get the change in time in seconds 
	lastFrameTime = currentFrameTime; //prepare for the next update. 
	glfwPollEvents(); //this completes any unfinished task 

}

float DisplayManager::getFrameTimeSeconds() {
	return delta;
}

double DisplayManager::getAspectRatio() {
	return (double)this->WIDTH / (double)this->HEIGHT;
}

int DisplayManager::getHeight() {
	return HEIGHT;
}

int DisplayManager::getWidth() {
	return WIDTH;
}

void DisplayManager::setHeight(int height) {
	this->HEIGHT = height;
}

void DisplayManager::setWidth(int width) {
	this->WIDTH = width;
}

void DisplayManager::closeDisplay() {

	//insert logic of closeDisplay
	glfwTerminate();

}

float DisplayManager::getCurrentTime() {

	//currentFrame = glfwGetTime();
	//deltaTime = currentFrame - lastFrame;
	//lastFrame = currentFrame;
	//std::cout << "The glfwGetTimeValue is " << glfwGetTimerValue() << std::endl;
	//std::cout << "The glfwGetTime() = " << glfwGetTime() << std::endl;
	//std::cout << "So " << glfwGetTime() << " * " << 1000 << " / " << glfwGetTimerValue() << " = " << glfwGetTime() * 1000 / glfwGetTimerValue() << std::endl;
	//std::cout << "inside of getCurrentTime, the clock() is " << float(clock()) << " and the CLOCKS_PER_SEC is " << float(CLOCKS_PER_SEC) << "so clock() / CLOCKS_PER_SEC = " << float(clock()) / float(CLOCKS_PER_SEC) << std::endl;
	float tester = float(clock()) / float(CLOCKS_PER_SEC);
	//std::cout << "tester is equal to " << tester << std::endl;
	return tester;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	std::cout << "callback in display manager called..." << std::endl;
	glfwSetWindowSize(window, width, height);
	//void* data = glfwGetWindowUserPointer(window); //obtain the pointer attribute - this allows us to access functions without having to create a new object

	//DisplayManager *disp = static_cast<DisplayManager *>(data); //use a pointer to access the camera class
	//disp->resize_handler(width, height);
																//then use the obtained access to call the mouse_handler (below)
																//glViewport(0, 0, width, height);

}

void DisplayManager::resize_handler(int width, int height) {
	std::cout << "Resize handler called - width is " << width << " and height is " << height << std::endl;
	WIDTH = width;
	HEIGHT = height;
	std::cout << "Viewport being set to width: " << WIDTH << " and height: " << HEIGHT << std::endl;
	//glViewport(0, 0, WIDTH, HEIGHT);
	//glfwSetWindowSize(window)
}

