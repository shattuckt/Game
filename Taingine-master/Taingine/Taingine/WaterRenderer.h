#pragma once
#include "Loader.h"
#include "WaterShader.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"
#include "Maths.h"
class WaterRenderer
{
private:
	RawModel quad;
	WaterShader* shader;
	WaterFrameBuffers waterFbos;
	DisplayManager* display;

	float moveFactor; //For the ripple effect of the water

	int dudvTexture;
	int normalMap;

public:
	WaterRenderer(Loader loader, WaterShader* shaders, glm::mat4 projectionMatrix, WaterFrameBuffers wFbos, DisplayManager* displays);

	void render(std::vector<WaterTile> water, glm::mat4 viewMatrix, glm::vec3 cameraPosition, Light sun);
	void prepareRender(glm::mat4 viewMatrix, glm::vec3 cameraPosition, Light sun);
	void unbind();
	void setUpVAO(Loader loader);

	~WaterRenderer(void);
};

