#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

class Window; //try taking this out later. see if friend delcaration is good enough.

class WindowBuilder{
	friend class Window;

private:
	int width;
	int height;
	const char* title = "Sacrosanct v0.1";

	bool isFullscreen = false;
	bool vsync = true;
	GLFWimage* icon = NULL;
	int minWidth = 120;
	int minHeight = 120;
	int fps = 100;
	int maxWidth = GLFW_DONT_CARE; //This means that there wont be a size limit to the window. 
	int maxHeight = GLFW_DONT_CARE;
	int samples = 0;

	GLFWwindow* createWindow(const GLFWvidmode* vidMode);
	void setWindowHints(const GLFWvidmode* vidMode);
	void applyWindowSettings(GLFWwindow* windowId);

protected:
	WindowBuilder(int width, int height, std::string title);

public:
	Window* create();
	WindowBuilder* fullscreen(bool fullscreen);
	WindowBuilder* setFps(int fps);
	WindowBuilder* setVsync(bool vsync);
	WindowBuilder* setMSAA(bool enable);
	WindowBuilder* withIcon(std::vector<GLFWimage> icon);
	WindowBuilder* setMinSize(int width, int height);
	WindowBuilder* setMaxSize(int width, int height);
	WindowBuilder* withoutSizeLimits();

	


	
};

