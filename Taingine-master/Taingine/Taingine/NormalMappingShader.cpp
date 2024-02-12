#include "NormalMappingShader.h"

const int MAXX_LIGHTS = 4;

getPaths getPather;
const std::string NormalMappingShader::VERTEX_FILE = getPather.GetCurrentWorkingDir() + "\\normalMapVShader.txt";
const std::string NormalMappingShader::FRAGMENT_FILE = getPather.GetCurrentWorkingDir() + "\\normalMapFShader.txt";


void NormalMappingShader::normalMappingShaders() {
	NormalMappingShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);
	NormalMappingShader::bindAttributes();
	NormalMappingShader::getAllUniformLocations();
}

void NormalMappingShader::bindAttributes() { //bind all the attributes needed for the shader..
	NormalMappingShader::bindAttribute(0, "position");
	NormalMappingShader::bindAttribute(1, "textureCoordinates");
	NormalMappingShader::bindAttribute(2, "normal");
	NormalMappingShader::bindAttribute(3, "tangent");
}

void NormalMappingShader::getAllUniformLocations() {
	location_transformationMatrix = NormalMappingShader::getUniformLocation("transformationMatrix");
	location_projectionMatrix = NormalMappingShader::getUniformLocation("projectionMatrix");
	location_viewMatrix = NormalMappingShader::getUniformLocation("viewMatrix");
	location_shineDamper = NormalMappingShader::getUniformLocation("shineDamper");
	location_reflectivity = NormalMappingShader::getUniformLocation("reflectivity");
	location_skyColour = NormalMappingShader::getUniformLocation("skyColour");
	location_numberOfRows = NormalMappingShader::getUniformLocation("numberOfRows");
	location_offset = NormalMappingShader::getUniformLocation("offset");
	location_plane = NormalMappingShader::getUniformLocation("plane");
	location_modelTexture = NormalMappingShader::getUniformLocation("modelTexture");
	location_normalMap = NormalMappingShader::getUniformLocation("normalMap");

	for (int i = 0; i<MAXX_LIGHTS; i++) {
		location_lightPositionEyeSpace.push_back(NormalMappingShader::getUniformLocation("lightPositionEyeSpace[" + std::to_string(static_cast<long long>(i)) + "]"));
		location_lightColour.push_back(NormalMappingShader::getUniformLocation("lightColour[" + std::to_string(static_cast<long long>(i)) + "]"));
		location_attenuation.push_back(NormalMappingShader::getUniformLocation("attenuation[" + std::to_string(static_cast<long long>(i)) + "]"));
	}
}

void NormalMappingShader::connectTextureUnits() { //Essentially we need to tell the shader which texture coord location to sample when it is sampling 
	NormalMappingShader::loadInt(location_modelTexture, 0);
	NormalMappingShader::loadInt(location_normalMap, 1);
}

void NormalMappingShader::loadClipPlane(glm::vec4 plane) {
	NormalMappingShader::load4DVector(location_plane, plane);
}

void NormalMappingShader::loadNumberOfRows(int numberOfRows) {
	NormalMappingShader::loadFloat(location_numberOfRows, numberOfRows);
}

void NormalMappingShader::loadOffset(float x, float y) {
	NormalMappingShader::load2DVector(location_offset, glm::vec2(x, y));
}

void NormalMappingShader::loadSkyColour(float r, float g, float b) {
	NormalMappingShader::load3DVector(location_skyColour, glm::vec3(r, g, b));
}

void NormalMappingShader::loadShineVariables(float damper, float reflectivity) {
	NormalMappingShader::loadFloat(location_shineDamper, damper);
	NormalMappingShader::loadFloat(location_reflectivity, reflectivity);
}

void NormalMappingShader::loadTransformationMatrix(glm::mat4 matrix) {
	NormalMappingShader::loadMatrix(location_transformationMatrix, matrix);
}

void NormalMappingShader::loadLights(std::vector<Light> lights, glm::mat4 viewMatrix) {
	for (int i = 0; i<MAXX_LIGHTS; i++) {
		if (i<lights.size()) {
			NormalMappingShader::load3DVector(location_lightPositionEyeSpace[i], getEyeSpacePosition(lights[i], viewMatrix));
			NormalMappingShader::load3DVector(location_lightColour[i], lights[i].getColour());
			NormalMappingShader::load3DVector(location_attenuation[i], lights[i].getAttenuation());
		}
		else {
			NormalMappingShader::load3DVector(location_lightPositionEyeSpace[i], glm::vec3(0, 0, 0));
			NormalMappingShader::load3DVector(location_lightColour[i], glm::vec3(0, 0, 0));
			NormalMappingShader::load3DVector(location_attenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void NormalMappingShader::loadViewMatrix(glm::mat4 viewMatrix) {
	NormalMappingShader::loadMatrix(location_viewMatrix, viewMatrix);
}

void NormalMappingShader::loadProjectionMatrix(glm::mat4 projection) {
	NormalMappingShader::loadMatrix(location_projectionMatrix, projection);
}

glm::vec3 NormalMappingShader::getEyeSpacePosition(Light light, glm::mat4 viewMatrix) {
	glm::vec3 position = light.getPosition();
	glm::vec4 eyeSpacePos = glm::vec4(position.x, position.y, position.z, 1.0f);
	glm::vec3 positions = position * position;
	eyeSpacePos = viewMatrix * eyeSpacePos; //this is meant to transform the eyeSpacePos using the viewMatrix. 

											//glm::mat4.transform(viewMatrix, eyeSpacePos, eyeSpacePos);
	return glm::vec3(eyeSpacePos);
}



NormalMappingShader::~NormalMappingShader(void)
{
}
