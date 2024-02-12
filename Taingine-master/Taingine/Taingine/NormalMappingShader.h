#pragma once
#include "ShaderProgram.h"
#include "getPaths.h"
//#include "Camera.h"
#include "Light.h"

class NormalMappingShader : public ShaderProgram
{
private:
	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	unsigned int location_transformationMatrix;
	unsigned int location_projectionMatrix;
	unsigned int location_viewMatrix;
	std::vector<unsigned int> location_lightPositionEyeSpace; //this is in tangent space I believe 
	std::vector<unsigned int> location_lightColour;
	std::vector<unsigned int> location_attenuation;
	unsigned int location_shineDamper;
	unsigned int location_reflectivity;
	unsigned int location_skyColour;
	unsigned int location_numberOfRows;
	unsigned int location_offset;
	unsigned int location_plane;
	unsigned int location_modelTexture;
	unsigned int location_normalMap;

public:
	NormalMappingShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

	void normalMappingShaders();
	void bindAttributes();
	void getAllUniformLocations();

	void connectTextureUnits();
	void loadClipPlane(glm::vec4 plane);
	void loadNumberOfRows(int numberOfRows);
	void loadOffset(float x, float y);
	void loadSkyColour(float r, float g, float b);
	void loadShineVariables(float damper, float reflectivity);
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadLights(std::vector<Light> lights, glm::mat4 viewMatrix);
	void loadViewMatrix(glm::mat4 viewMatrix);
	void loadProjectionMatrix(glm::mat4 projection);

	glm::vec3 getEyeSpacePosition(Light light, glm::mat4 viewMatrix);

	~NormalMappingShader(void);
};

