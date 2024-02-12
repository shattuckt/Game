#pragma once
#include "ShaderProgram.h"
//#include "Camera.h"
#include "Light.h"
#include "getPaths.h"

class WaterShader : public ShaderProgram
{
private:

	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	unsigned int location_modelMatrix;
	unsigned int location_viewMatrix;
	unsigned int location_projectionMatrix;
	unsigned int location_reflectionTexture;
	unsigned int location_refractionTexture;
	unsigned int location_dudvMap;
	unsigned int location_moveFactor;
	unsigned int location_cameraPosition;
	unsigned int location_normalMap;
	unsigned int location_lightColour;
	unsigned int location_lightPosition;
	unsigned int location_depthMap;

public:
	WaterShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}
	void WaterShaders();

	void bindAttributes();
	void getAllUniformLocations();

	void connectTextureUnites();

	void loadLight(Light sun);
	void loadMoveFactor(float factor);
	void loadProjectionMatrix(glm::mat4 projection);
	void loadViewMatrix(glm::mat4 viewMatrix, glm::vec3 cameraPosition);
	void loadModelMatrix(glm::mat4 modelMatrix);
	//glm::mat4 createViewMatrix(Camera* camera);

	~WaterShader(void);
};

