#include "GameManager.h"
Engine* GameManager::engine;
//MasterSceneRenderer* GameManager::renderer;
//MouseRay GameManager::mouseRay;
//CityBuilderGuis GameManager::gameUI;

//ResourceRepository GameManager::resourceRepos;

//Scene GameManager::scene;
//ICamera GameManager::camera;

//BasicRoadPlacer GameManager::roadPlacer;
//PlacementManager GameManager::buildingPlacer;

void GameManager::init(EngineConfigs configs) {
	engine = Engine::init(configs);
}
/*
void GameManager::update();
Scene GameManager::getScene();
MasterSceneRenderer GameManager::getRenderSystem();
ResourceRepository GameManager::getResourceRepository();
RoadSystems GameManager::getRoadSystem();
void GameManager::cleanUp();
World GameManager::getWorld();
Engine GameManager::getEngine();
ICamera GameManager::getCamera();
MouseRay GameManager::getMouseRay();
BasicRoadPlacer GameManager::getRoadPlacer();
PlacementManager GameManager::getBuildingPlacer();
bool GameManager::readyToClose();
Camera GameManager::setUpCamera();*/