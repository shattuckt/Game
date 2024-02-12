#include "WaterShader.h"

getPaths getPathsss;
const std::string WaterShader::VERTEX_FILE = getPathsss.GetCurrentWorkingDir() + "\\waterVertex.txt";
const std::string WaterShader::FRAGMENT_FILE = getPathsss.GetCurrentWorkingDir() + "\\waterFragment.txt";


void WaterShader::WaterShaders() {

	cout << "about to create shader from " << VERTEX_FILE << " and " << VERTEX_FILE << endl;
	WaterShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);

	WaterShader::bindAttributes();
	WaterShader::getAllUniformLocations();

}

void WaterShader::bindAttributes() {  //bind all the attributes needed for the shader..
	WaterShader::bindAttribute(0, "position");
}

void WaterShader::getAllUniformLocations() { //get all the locations needed for the shader...
	location_modelMatrix = WaterShader::getUniformLocation("modelMatrix");
	location_projectionMatrix = WaterShader::getUniformLocation("projectionMatrix");
	location_viewMatrix = WaterShader::getUniformLocation("viewMatrix");
	location_reflectionTexture = WaterShader::getUniformLocation("reflectionTexture");
	location_refractionTexture = WaterShader::getUniformLocation("refractionTexture");
	location_dudvMap = WaterShader::getUniformLocation("dudvMap");
	location_moveFactor = WaterShader::getUniformLocation("moveFactor");
	location_cameraPosition = WaterShader::getUniformLocation("cameraPosition");
	location_normalMap = WaterShader::getUniformLocation("normalMap");
	location_lightColour = WaterShader::getUniformLocation("lightColour");
	location_lightPosition = WaterShader::getUniformLocation("lightPosition");
	location_depthMap = WaterShader::getUniformLocation("depthMap");

}

void WaterShader::connectTextureUnites() {
	WaterShader::loadInt(location_reflectionTexture, 0); //sample this texture from texture unit 0
	WaterShader::loadInt(location_refractionTexture, 1); //sample this texture from texture unit 1
	WaterShader::loadInt(location_dudvMap, 2); //sample this texture from texture unit 2 
	WaterShader::loadInt(location_normalMap, 3); //sample this texture from texture unit 3
	WaterShader::loadInt(location_depthMap, 4); //sample this texture from texture unit 4
}

void WaterShader::loadLight(Light sun) {
	WaterShader::load3DVector(location_lightColour, sun.getColour());     //Load up the colors for the waterFragment
	WaterShader::load3DVector(location_lightPosition, sun.getPosition()); //Load up the positions for the waterVertex
}

void WaterShader::loadMoveFactor(float factor) {
	WaterShader::loadFloat(location_moveFactor, factor);
}

void WaterShader::loadProjectionMatrix(glm::mat4 projection) {
	WaterShader::loadMatrix(location_projectionMatrix, projection);
}

void WaterShader::loadViewMatrix(glm::mat4 viewMatrix, glm::vec3 cameraPosition) {
	//glm::mat4 viewMatrix = createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
	WaterShader::load3DVector(location_cameraPosition, cameraPosition);
}

void WaterShader::loadModelMatrix(glm::mat4 modelMatrix) {
	loadMatrix(location_modelMatrix, modelMatrix);
}

//Note: this doesnt use "Roll" because it wasnt used in the tutorial. 
/*glm::mat4 WaterShader::createViewMatrix(Camera* camera) {
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

WaterShader::~WaterShader(void)
{
}
