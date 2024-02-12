#include "Window.h"

WindowBuilder* Window::newWindow(int width, int height, std::string title) {
	return new WindowBuilder(width, height, title);
}

Window::Window(GLFWwindow* id, int desiredWidth, int desiredHeight, int fps, bool fullscreen, bool vsync) {
	this->id = id;
	this->desiredWidth = desiredWidth;
	this->desiredHeight = desiredHeight;
	this->fullscreen = fullscreen;
	this->vsync = vsync;
	this->fps = fps;
	this->frameSync = new Sync(fps);
	getInitialWindowSizes();
	addScreenSizeListener();
	addPixelSizeListener();
}

GLFWwindow* Window::getId(){
	return id;
}
int Window::getScreenCoordWidth() {
	return this->widthScreenCoords;
}
int Window::getScreenCoordHeight() {
	return this->heightScreenCoords;
}
int Window::getFps() {
	return this->fps;
}
float Window::getAspectRatio() {
	return (float)this->pixelWidth / this->pixelHeight;
}
int Window::getPixelHeight() {
	return this->pixelHeight;
}
int Window::getPixelWidth() {
	return this->pixelWidth;
}
bool Window::isFullScreen() {
	return this->fullscreen;
}
bool Window::isVsync() {
	return this->vsync;
}
void Window::setFps(int fps) {
	frameSync->setFps(fps);
}
void Window::addSizeChangeListener(WindowSizeListener* listener) {
	listeners.push_back(listener);
}
void Window::update() {
	glfwSwapBuffers(id);
	glfwPollEvents();
	frameSync->sync();
}
bool Window::closeButtonPressed() {
	return glfwWindowShouldClose(this->id);
}
void Window::destroy() {
	//glfwFreeCallbacks(id);
	glfwDestroyWindow(this->id);
	glfwTerminate();
	//glfwSetErrorCallback()

}
void Window::setVsync(bool vsync) {
	this->vsync = vsync;
	glfwSwapInterval(vsync ? 1 : 0);
}
void Window::goFullScreen(bool fullscreen) {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
	if (fullscreen) {
		switchToFullScreen(monitor, vidMode);
	}
	else {
		switchToWindowed(vidMode);
	}
	this->fullscreen = fullscreen;
}

void Window::switchToFullScreen(GLFWmonitor* monitor, const GLFWvidmode* vidMode) {
	this->desiredWidth = widthScreenCoords;
	this->desiredHeight = heightScreenCoords;
	glfwSetWindowMonitor(this->id, monitor, 0, 0, desiredWidth, desiredHeight, vidMode->refreshRate);
}
void Window::switchToWindowed(const GLFWvidmode* vidMode) {
	glfwSetWindowMonitor(this->id, NULL, 0, 0, desiredWidth, desiredHeight, vidMode->refreshRate);
	glfwSetWindowPos(this->id, (vidMode->width - desiredWidth) / 2, (vidMode->height - desiredHeight) / 2);
}

void Window::addScreenSizeListener() {
	glfwSetWindowUserPointer(this->id, this);

	glfwSetWindowSizeCallback(this->id, [](GLFWwindow* window, int width, int height) {
		void* data = glfwGetWindowUserPointer(window);
		Window* windowObj = static_cast<Window*>(data);

		if (windowObj->validSizeChange(width, height, windowObj->widthScreenCoords, windowObj->heightScreenCoords)) {
			windowObj->widthScreenCoords = width;
			windowObj->heightScreenCoords = height;
		}
	});

}
void Window::addPixelSizeListener() {
	glfwSetWindowUserPointer(this->id, this);
	glfwSetFramebufferSizeCallback(this->id, [](GLFWwindow* window, int width, int height) {
		void* data = glfwGetWindowUserPointer(window);
		Window* windowObj = static_cast<Window*>(data);
		if (windowObj->validSizeChange(width, height, windowObj->pixelWidth, windowObj->pixelHeight)) {
			windowObj->pixelWidth = width;
			windowObj->pixelHeight = height;
			windowObj->notifyListeners();
		}
	});
}
void Window::getInitialWindowSizes() {
	getInitialScreenSize();
	getInitialPixelSize();
}
void Window::getInitialScreenSize() {
	int height, width;
	glfwGetWindowSize(this->id, &width, &height);
	this->widthScreenCoords = width;
	this->heightScreenCoords = height;
}
void Window::getInitialPixelSize() {
	int pixelHeight, pixelWidth;
	glfwGetFramebufferSize(this->id, &pixelWidth, &pixelHeight);
	this->pixelWidth = pixelWidth;
	this->pixelHeight = pixelHeight;
}
bool Window::validSizeChange(int newWidth, int newHeight, int oldWidth, int oldHeight) {
	if (newWidth == 0 || newHeight == 0) {
		return false;
	}
	return newWidth != oldWidth || newHeight != oldHeight;
}
void Window::notifyListeners() {
	for (int i = 0; i < listeners.size(); i++) {
		listeners[i]->sizeChanged(pixelWidth, pixelHeight);
	}
}