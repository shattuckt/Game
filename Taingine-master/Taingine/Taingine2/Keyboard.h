#pragma once
#include <unordered_set>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard{
private:
	std::unordered_set<int> keysPressedThisFrame;
	std::unordered_set<int> keysRepeatedThisFrame;
	std::unordered_set<int> keysReleasedThisFrame;
	std::unordered_set<int> keysDown;
	std::string charsThisFrame;

	void reportKeyPress(int key);
	void reportKeyRelease(int key);
	void addTextListener(GLFWwindow* windowId);
	void addKeyListener(GLFWwindow* windowId);

public:
	Keyboard(GLFWwindow* windowId);
	void update();
	bool isKeyDown(int key);
	std::string getChars();
	bool keyPressEvent(int key);
	bool keyPressEvent(int key, bool checkRepeats);
};

