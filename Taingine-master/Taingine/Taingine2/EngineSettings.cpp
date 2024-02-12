#include "EngineSettings.h"

EngineConfigs EngineSettings::getConfigs() {
	EngineConfigs configs = EngineConfigs::getDefaultConfigs();
	configs.windowTitle = "Sacrosanct v0.1";
	configs.vsync = false;
	configs.msaa = true;
	configs.fps = 100;
	configs.UiSize = 1;
	//configs.fullscreen = true;
	configs.windowMinHeight = 0;
	configs.windowMinWidth = 0;
	configs.windowWidth = 1600;
	configs.windowHeight = 900;
	configs.defaultState = State::NORMAL;
	configs.initialState = State::SPLASH_SCREEN;
	return configs;
}