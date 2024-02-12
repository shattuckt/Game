#pragma once
#include "TerrainShader.h"
#include "DisplayManager.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Terrain.h"
#include "Runable.h"
#include <list>
class TerrainRenderer
{
private:
	TerrainShader shaders;
	DisplayManager* display;

public:
	TerrainRenderer(TerrainShader shader, DisplayManager* newDisplay, glm::mat4 projectionMatrix);
	TerrainRenderer(void) {};
	void render(std::vector<Terrain*> terrains);
	void prepareTerrain(Terrain* terrain);
	void bindTextures(Terrain* terrain);
	void unbindTexturedModel();
	void loadModelMatrix(Terrain* terrain);

	virtual void run();

	~TerrainRenderer(void);
};

