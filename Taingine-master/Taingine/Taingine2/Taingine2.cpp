// Taingine2.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "EngineSettings.h"
#include "GameManager.h"

int main(){
	EngineConfigs configs = EngineSettings::getConfigs();
	std::cout << "test initial state: " << configs.defaultState << std::endl;
	GameManager::init(configs);
}