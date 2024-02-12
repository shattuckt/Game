#pragma once
#include "ShaderProgram.h"
#include "getPaths.h"
#include "Light.h"

class StaticShader : public ShaderProgram
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
	unsigned int location_useFakeLighting;
	unsigned int location_skyColour;
	unsigned int location_numberOfRows;
	unsigned int location_offset;
	unsigned int location_plane;

public:

	StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

	void StaticShaders();
	void bindAttributes();
	void getAllUniformLocations();

	void loadClipPlane(glm::vec4 plane);
	void loadOffset(float x, float y);
	void loadNumberOfRows(int numberOfRows);
	void loadSkyColour(float r, float g, float b);
	void loadFakeLightingVariable(bool useFake);
	void loadShineVariables(float damper, float reflectivity);
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 projection);
	void loadLights(std::vector<Light> lights);
	void loadViewMatrix(glm::mat4 viewMatrix);
	//glm::mat4 createViewMatrix(Camera* camera);

};
