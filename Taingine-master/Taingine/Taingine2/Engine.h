#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "EngineConfigs.h"
#include "Timer.h"
#include "StateManager.h"
#include "EngineFiles.h"
#include "IconLoader.h"
#include <filesystem>

class Engine{
private:
	Window* window;
	Keyboard* keyboard;
	Mouse* mouse;
	Timer* timer;
	StateManager* stateManager;

	bool closeFlag = false;

	Engine(Window* window, Mouse* mouse, Keyboard* keyboard, Timer* timer, StateManager* stateManager);
	static void initOpenGl(int pixelWidth, int pixelHeight);
	static Window* setUpWindow(EngineConfigs configs);
	static void initUiMaster(Window* window, Mouse* mouse, int minWidth, int minHeight, float uiSize);
	static void initResFolder();
	static std::vector<GLFWimage> loadWindowIcon();

public:
	static Engine* init(EngineConfigs configs);
	Window* getWindow();
	Keyboard* getKeyboard();
	Mouse* getMouse();
	StateManager* getStateManager();
	float getDeltaSeconds();
	void update();
	void cleanUp();
	void requestClose();
	bool isCloseRequested();

	
};

