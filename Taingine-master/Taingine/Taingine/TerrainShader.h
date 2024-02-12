#pragma once
#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include "getPaths.h"
//#include "Camera.h"
#include "Light.h"

class TerrainShader : public ShaderProgram
{
private:

	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	unsigned int location_transformationMatrix;
	unsigned int location_projectionMatrix;
	unsigned int location_viewMatrix;
	std::vector<unsigned int> location_lightPosition; //An array of locations is needed for each color position 
	std::vector<unsigned int> location_lightColour; //An array of locations is needed for each color's.. color.
	std::vector<unsigned int> location_attenuation;
	unsigned int location_shineDamper;
	unsigned int location_reflectivity;
	unsigned int location_skyColour;
	unsigned int location_backgroundTexture;
	unsigned int location_rTexture;
	unsigned int location_gTexture;
	unsigned int location_bTexture;
	unsigned int location_blendMap;
	unsigned int location_plane;

public:

	TerrainShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {
		TerrainShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);
		location_bTexture = -1;
		TerrainShader::bindAttributes();
		TerrainShader::getAllUniformLocations();

	}

	void TerrainShaders();
	void bindAttributes();
	void getAllUniformLocations();

	void connectTextureUnits();
	void loadClipPlane(glm::vec4 clipPlane);
	void loadSkyColour(float r, float g, float b);
	void loadShineVariables(float damper, float reflectivity);
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 projection);
	void loadLights(std::vector<Light> lights);
	void loadViewMatrix(glm::mat4 viewMatrix);
	//glm::mat4 createViewMatrix(Camera* camera);

};
