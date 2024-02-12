#include "SkyboxShader.h"

getPaths getpathsss;
const std::string SkyboxShader::VERTEX_FILE = getpathsss.GetCurrentWorkingDir() + "\\skyboxVertexShader.txt";
const std::string SkyboxShader::FRAGMENT_FILE = getpathsss.GetCurrentWorkingDir() + "\\skyboxFragmentShader.txt";

const float ROTATE_SPEED = 0.0f; //Dictates how quickly the scene rotates - was set to 1

void SkyboxShader::SkyboxShaders() {

	SkyboxShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);

	SkyboxShader::bindAttributes();
	SkyboxShader::getAllUniformLocations();

	rotation = 0;

}

void SkyboxShader::loadProjectionMatrix(glm::mat4 projection) {
	SkyboxShader::loadMatrix(location_projectionMatrix, projection);
}

void SkyboxShader::loadViewMatrix(glm::mat4 viewMatrix, DisplayManager* display) {
	//glm::mat4 viewMatrix = createViewMatrix(camera);
	//this prevents the skybox from translating to the origin (the last column of a 4x4 matrix is the translation)
	//otherwise the texture would move with the camera I believe 
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
	//Then, we want to rotate the skybox so that it appears that the clouds are moving. so each second we add a constant speed to the rotation (which starts at zero)
	//std::cout << " that total is added to the rotation, currently " << rotation << " so that plus " << ROTATE_SPEED * display.getFrameTimeSeconds() << " = " << rotation + ROTATE_SPEED * display.getFrameTimeSeconds() << std::endl;
	rotation += ROTATE_SPEED * display->getFrameTimeSeconds();                                //In each frame, the skybox will be rotated by this amount 
	viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0, 1, 0)); // then apply the rotation to the viewMatrix
	loadMatrix(location_viewMatrix, viewMatrix);

}

void SkyboxShader::getAllUniformLocations() { //get all the locations needed for the shader...
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_fogColour = getUniformLocation("fogColour");
	location_cubeMap = getUniformLocation("cubeMap");
	location_cubeMap2 = getUniformLocation("cubeMap2");
	location_blendFactor = getUniformLocation("blendFactor");
}

void SkyboxShader::bindAttributes() { //bind all the attributes needed for the shader..
	bindAttribute(0, "position");
}

void SkyboxShader::loadFogColour(float r, float g, float b) {
	SkyboxShader::load3DVector(location_fogColour, glm::vec3(r, g, b));
}

void SkyboxShader::loadBlendFactor(float blend) {
	SkyboxShader::loadFloat(location_blendFactor, blend);
}

void SkyboxShader::connectTextureUnits() { //Essentially we need to tell the shader which texture coord location to sample when it is sampling 
	SkyboxShader::loadInt(location_cubeMap, 0);
	SkyboxShader::loadInt(location_cubeMap2, 1);
}

//Note: this doesnt use "Roll" because it wasnt used in the tutorial. 
/*glm::mat4 SkyboxShader::createViewMatrix(Camera* camera) {

	glm::mat4 viewMatrix;
	glm::vec3 cameraPos = camera->getCameraPosition();
	glm::vec3 cameraFront; // = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 front;
	front.x = cos(glm::radians(camera->getPitch())) * cos(glm::radians(camera->getYaw()));
	front.y = sin(glm::radians(camera->getPitch()));
	front.z = cos(glm::radians(camera->getPitch())) * sin(glm::radians(camera->getYaw()));
	cameraFront = glm::normalize(front); //depicts how high or low the camera is looking 
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	return viewMatrix;

}*/

SkyboxShader::~SkyboxShader(void) {}