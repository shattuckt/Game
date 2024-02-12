#pragma once
#include "ShaderProgram.h"
#include "getPaths.h"
#include "DisplayManager.h"
#include <glm-0.9.8.5\glm\gtc\matrix_transform.hpp>

class SkyboxShader : public ShaderProgram
{
private:
	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	unsigned int location_projectionMatrix;
	unsigned int location_viewMatrix;
	unsigned int location_fogColour;
	unsigned int location_cubeMap;
	unsigned int location_cubeMap2;
	unsigned int location_blendFactor;

	float rotation;

public:
	SkyboxShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

	void SkyboxShaders();

	void loadProjectionMatrix(glm::mat4 projection);

	void loadViewMatrix(glm::mat4 viewMatrix, DisplayManager* display);

	void getAllUniformLocations();

	void bindAttributes();

	void loadFogColour(float r, float g, float b);

	void loadBlendFactor(float blend);

	void connectTextureUnits();

	//glm::mat4 createViewMatrix(Camera* camera);

	~SkyboxShader(void);

};


