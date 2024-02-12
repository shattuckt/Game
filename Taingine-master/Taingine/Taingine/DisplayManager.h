#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <ctime>

using namespace std;

class DisplayManager
{

private:

	//Declare all instance variables here: 
	GLFWwindow* window;
	float lastFrameTime;
	float delta;

	int WIDTH;
	int HEIGHT;

public:
	//Constructor
	//Note: constructors can't return anything so that is why it does not specify a return type - not even void
	DisplayManager();
	void createDisplay();
	void updateDisplay();

	GLFWwindow* getWindow();

	float getFrameTimeSeconds();
	double getAspectRatio();
	int getHeight();
	int getWidth();
	void setHeight(int height);
	void setWidth(int width);

	void closeDisplay();
	float getCurrentTime();

	void resize_handler(int width, int height);

	//~DisplayManager(void);
};

