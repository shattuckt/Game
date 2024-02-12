#pragma once
#include <iostream>
#include "RawModel.h"
#include "SkyboxShader.h"
#include "Loader.h"

class SkyboxRenderer
{
private:

	RawModel cube;
	Loader loaded;
	int dayTexture;
	int nightTexture;
	float time;

	SkyboxShader shaders;

public:
	SkyboxRenderer(Loader loader, glm::mat4 projectionMatrix);
	SkyboxRenderer(void) {}

	void render(glm::mat4 viewMatrix, DisplayManager* display, float r, float g, float b);
	void bindTextures(DisplayManager* display);

	~SkyboxRenderer(void);
};

