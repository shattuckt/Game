#pragma once
#include <unordered_set>

#include "Window.h"
#include "MouseButton.h"

class Mouse{
private:
	Window* window;

	std::unordered_set<int> buttonsDown;
	std::unordered_set<int> buttonsClickedThisFrame;
	std::unordered_set<int> buttonsReleasedThisFrame;

	double x, y;
	double dx, dy;
	double scroll;
	double lastX, lastY;

	void reportButtonClick(int button);
	void reportButtonRelease(int button);
	void updateDeltas();
	void addMoveListener(GLFWwindow* windowId);
	void addClickListener(GLFWwindow* windowId);
	void addScrollListener(GLFWwindow* windowId);

public:
	Mouse(Window* window);
	bool isButtonDown(MouseButton button);
	bool isClickEvent(MouseButton button);
	bool isReleaseEvent(MouseButton button);
	double getX();
	double getY();
	double getDx();
	double getDy();
	double getScroll();
	void update();	
};

