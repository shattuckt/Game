#include "Mouse.h"

Mouse::Mouse(Window* window) {
	this->window = window;
	addMoveListener(window->getId());
	addClickListener(window->getId());
	addScrollListener(window->getId());
}
bool Mouse::isButtonDown(MouseButton button) {
	std::unordered_set<int>::const_iterator found = buttonsDown.find(button);
	return (found == buttonsDown.end()) ? false : true;
}
bool Mouse::isClickEvent(MouseButton button) {
	std::unordered_set<int>::const_iterator found = buttonsClickedThisFrame.find(button);
	return (found == buttonsClickedThisFrame.end()) ? false : true;
}
bool Mouse::isReleaseEvent(MouseButton button) {
	std::unordered_set<int>::const_iterator found = buttonsReleasedThisFrame.find(button);
	return (found == buttonsReleasedThisFrame.end()) ? false : true;
}
double Mouse::getX() {
	return x;
}
double Mouse::getY() {
	return y;
}
double Mouse::getDx() {
	return dx;
}
double Mouse::getDy() {
	return dy;
}
double Mouse::getScroll() {
	return scroll;
}
void Mouse::update() {
	buttonsClickedThisFrame.clear();
	buttonsReleasedThisFrame.clear();
	updateDeltas();
	this->scroll = 0;
}

void Mouse::reportButtonClick(int button) {
	buttonsClickedThisFrame.insert(button);
	buttonsDown.insert(button);
}
void Mouse::reportButtonRelease(int button) {
	buttonsReleasedThisFrame.insert(button);
	buttonsDown.erase(button);
}
void Mouse::updateDeltas() {
	this->dx = x - lastX;
	this->dy = y - lastY;
	this->lastX = x;
	this->lastY = y;
}
void Mouse::addMoveListener(GLFWwindow* windowId) {
	glfwSetCursorPosCallback(windowId, [](GLFWwindow* window, double xpos, double ypos) {
		void* data = glfwGetWindowUserPointer(window);
		Mouse* mouseObj = static_cast<Mouse*>(data);
		mouseObj->x = (xpos / mouseObj->window->getScreenCoordWidth());
		mouseObj->y = (ypos / mouseObj->window->getScreenCoordHeight());
		});
}
void Mouse::addClickListener(GLFWwindow* windowId) {
	glfwSetMouseButtonCallback(windowId, [](GLFWwindow* window, int button, int action, int mods) {
		void* data = glfwGetWindowUserPointer(window);
		Mouse* mouseObj = static_cast<Mouse*>(data);
		if (action == GLFW_PRESS) {
			mouseObj->reportButtonClick(button);
		}
		else if (action == GLFW_RELEASE) {
			mouseObj->reportButtonRelease(button);
		}
		});
}
void Mouse::addScrollListener(GLFWwindow* windowId) {
	glfwSetScrollCallback(windowId, [](GLFWwindow* window, double xoffset, double yoffset) {
		void* data = glfwGetWindowUserPointer(window);
		Mouse* mouseObj = static_cast<Mouse*>(data);
		mouseObj->scroll = yoffset;
		});
}