#include "WindowBuilder.h"

WindowBuilder::WindowBuilder(int width, int height, std::string title) {
	this->width = width;
	this->height = height;
	//this->title = title;
}

Window* WindowBuilder::create() {
	//GLFWErrorCallback.createPrint(System.err).set(); not sure how to do the error callback TBH. 
	glfwInit();
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	setWindowHints(vidMode);
	GLFWwindow* windowId = createWindow(vidMode);
	applyWindowSettings(windowId);
	return new Window(windowId, width, height, fps, isFullscreen, vsync);

}

WindowBuilder* WindowBuilder::fullscreen(bool fullscreen) {
	this->isFullscreen = fullscreen;
	return this;
}
WindowBuilder* WindowBuilder::setFps(int fps) {
	this->fps = fps;
	return this;
}
WindowBuilder* WindowBuilder::setVsync(bool vsync) {
	this->vsync = vsync;
	return this;
}
WindowBuilder* WindowBuilder::setMSAA(bool enable) {
	this->samples = enable ? 4 : 0;
	return this;
}
WindowBuilder* WindowBuilder::withIcon(std::vector<GLFWimage> icon) {
	//this->icon[icon.size()];
	//std::copy(icon.begin(), icon.end(), this->icon);
	this->icon = icon.data();
	return this;
}
WindowBuilder* WindowBuilder::setMinSize(int width, int height) {
	this->minHeight = width;
	this->minHeight = height;
	return this;
}
WindowBuilder* WindowBuilder::setMaxSize(int width, int height) {
	this->maxHeight = height;
	this->maxWidth = width;
	return this;
}
WindowBuilder* WindowBuilder::withoutSizeLimits() {
	this->minWidth = GLFW_DONT_CARE;
	this->minHeight = GLFW_DONT_CARE;
	this->maxHeight = GLFW_DONT_CARE;
	this->maxWidth = GLFW_DONT_CARE;
	return this;
}

GLFWwindow* WindowBuilder::createWindow(const GLFWvidmode* vidMode) {
	if (isFullscreen) {
		return glfwCreateWindow(vidMode->width, vidMode->height, title, glfwGetPrimaryMonitor(), NULL);
	}
	else {
		GLFWwindow* windowId = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwSetWindowPos(windowId, (vidMode->width - width) / 2, (vidMode->height - height) / 2);
		return windowId;
	}
}
void WindowBuilder::applyWindowSettings(GLFWwindow* windowId) {
	glfwMakeContextCurrent(windowId);
	glfwSwapInterval(vsync ? 1 : 0);
	glfwSetWindowSizeLimits(windowId, minWidth, minHeight, maxWidth, maxHeight);
	glfwShowWindow(windowId);
	if (icon != NULL) { //TODO make this a better check for no icon. 
		glfwSetWindowIcon(windowId, 3, icon);
	}
}

void WindowBuilder::setWindowHints(const GLFWvidmode* vidMode) {
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
}