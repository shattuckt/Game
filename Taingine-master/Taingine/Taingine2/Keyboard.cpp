#include "Keyboard.h"

Keyboard::Keyboard(GLFWwindow* windowId) {
	addKeyListener(windowId);
	addTextListener(windowId);
}
void Keyboard::update() {
	keysPressedThisFrame.clear();
	keysReleasedThisFrame.clear();
	keysRepeatedThisFrame.clear();
	charsThisFrame = "";
}
bool Keyboard::isKeyDown(int key) {
	std::unordered_set<int>::const_iterator found = keysDown.find(key);
	return (found == keysDown.end()) ? false : true;
}
std::string Keyboard::getChars() {
	return charsThisFrame;
}
bool Keyboard::keyPressEvent(int key) {
	std::unordered_set<int>::const_iterator found = keysPressedThisFrame.find(key);
	return (found == keysPressedThisFrame.end()) ? false : true;
}
bool Keyboard::keyPressEvent(int key, bool checkRepeats) {
	std::unordered_set<int>::const_iterator found = keysPressedThisFrame.find(key);
	std::unordered_set<int>::const_iterator repeatFound = keysRepeatedThisFrame.find(key);
	return (found == keysPressedThisFrame.end() || checkRepeats && repeatFound == keysPressedThisFrame.end()) ? false : true;
}

//Private
void Keyboard::reportKeyPress(int key) {
	keysDown.insert(key);
	keysPressedThisFrame.insert(key);
}
void Keyboard::reportKeyRelease(int key) {
	std::cout << "Attempting to erase key - " << key << "probably will have to find?" << std::endl;
	keysDown.erase(key);
	keysReleasedThisFrame.insert(key);
}
void Keyboard::addTextListener(GLFWwindow* windowId) {
	glfwSetCharCallback(windowId, [](GLFWwindow* window, unsigned int codepoint) {
		void* data = glfwGetWindowUserPointer(window);
		Keyboard* keyboardObj = static_cast<Keyboard*>(data);
		keyboardObj->charsThisFrame += (char)codepoint;
		std::cout << "charsThisFrame = " << keyboardObj->charsThisFrame << std::endl;
		});
}
void Keyboard::addKeyListener(GLFWwindow* windowId) {
	glfwSetKeyCallback(windowId, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		void* data = glfwGetWindowUserPointer(window);
		Keyboard* keyboardObj = static_cast<Keyboard*>(data);
		if (action == GLFW_PRESS) {
			keyboardObj->reportKeyPress(key);
		}
		else if (action == GLFW_RELEASE) {
			keyboardObj->reportKeyRelease(key);
		}
		else if (action == GLFW_REPEAT) {
			keyboardObj->keysRepeatedThisFrame.insert(key);
		}
		});
}
