#pragma once
#include <iostream>
#include "State.h"

class EngineConfigs{
public:
	int languageID = 0;

	int windowWidth = 1280;
	int windowHeight = 720;

	int windowMinWidth = 600;
	int windowMinHeight = 350;
	float UiSize = 1;

	bool fullscreen = false;
	std::string windowTitle = "Sacrosanct v0.1";
	int fps = 100;
	bool vsync = true;
	bool msaa = true;

	State initialState;
	State defaultState;

	static EngineConfigs getDefaultConfigs();
private:
	EngineConfigs() {};
};

