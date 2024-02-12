#pragma once
#include "Engine.h"

class GameManager{
private:
	static Engine* engine;
	//static MasterSceneRenderer* renderer;
	//static MouseRay mouseRay;
	//static CityBuilderGuis gameUI;

	//static ResourceRepository resourceRepos;

	//static Scene scene;
	//static ICamera camera;

	//static BasicRoadPlacer roadPlacer;
	//static PlacementManager buildingPlacer;
public:
	static void init(EngineConfigs configs);
	/*
	static void update();
	static Scene getScene();
	static MasterSceneRenderer getRenderSystem();
	static ResourceRepository getResourceRepository();
	static RoadSystems getRoadSystem();
	static void cleanUp();
	static World getWorld();
	static Engine getEngine();
	static ICamera getCamera();
	static MouseRay getMouseRay();
	static BasicRoadPlacer getRoadPlacer();
	static PlacementManager getBuildingPlacer();
	static bool readyToClose();
	static Camera setUpCamera();*/


};

