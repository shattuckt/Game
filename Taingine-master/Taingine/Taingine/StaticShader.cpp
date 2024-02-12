#include "StaticShader.h"

const int MAX_LIGHTS = 4;

getPaths getPath;
const std::string StaticShader::VERTEX_FILE = getPath.GetCurrentWorkingDir() + "\\vertexShader.txt";
const std::string StaticShader::FRAGMENT_FILE = getPath.GetCurrentWorkingDir() + "\\fragmentShader.txt";

void StaticShader::StaticShaders() {

	//std::cout << "about to create shader from " << VERTEX_FILE << " and " << FRAGMENT_FILE << std::endl;
	StaticShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);

	StaticShader::bindAttributes();
	StaticShader::getAllUniformLocations();

}

void StaticShader::bindAttributes() { //bind all the attributes needed for the shader..
	StaticShader::bindAttribute(0, "position");
	StaticShader::bindAttribute(1, "textureCoordinates");
	StaticShader::bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations() { //get all the locations needed for the shader...
	location_transformationMatrix = StaticShader::getUniformLocation("transformationMatrix");
	location_projectionMatrix = StaticShader::getUniformLocation("projectionMatrix");
	location_viewMatrix = StaticShader::getUniformLocation("viewMatrix");
	//location_lightPosition = StaticShader::getUniformLocation("lightPosition");
	//location_lightColour = StaticShader::getUniformLocation("lightColour");
	location_shineDamper = StaticShader::getUniformLocation("shineDamper");
	location_reflectivity = StaticShader::getUniformLocation("reflectivity");
	location_useFakeLighting = StaticShader::getUniformLocation("useFakeLighting");
	location_skyColour = StaticShader::getUniformLocation("skyColour");
	location_numberOfRows = StaticShader::getUniformLocation("numberOfRows");
	location_offset = StaticShader::getUniformLocation("offset");
	location_plane = StaticShader::getUniformLocation("plane");

	for (int i = 0; i<MAX_LIGHTS; i++) {
		location_lightPosition.push_back(StaticShader::getUniformLocation("lightPosition[" + std::to_string(static_cast<long long>(i)) + "]"));
		location_lightColour.push_back(StaticShader::getUniformLocation("lightColour[" + std::to_string(static_cast<long long>(i)) + "]"));
		location_attenuation.push_back(StaticShader::getUniformLocation("attenuation[" + std::to_string(static_cast<long long>(i)) + "]"));
		//std::cout << "location_lightPos[" << i << "] is equal to " << StaticShader::getUniformLocation("lightPosition[" + std::to_string(static_cast<long long>(i)) + "]") << std::endl;
		//std::cout << "location_lightColour[" << i << "] is equal to " << StaticShader::getUniformLocation("lightColour[" + std::to_string(static_cast<long long>(i)) + "]") << std::endl;
	}


}

void StaticShader::loadClipPlane(glm::vec4 plane) {
	StaticShader::load4DVector(location_plane, plane);
}

void StaticShader::loadOffset(float x, float y) {
	StaticShader::load2DVector(location_offset, glm::vec2(x, y));
}

void StaticShader::loadNumberOfRows(int numberOfRows) {
	StaticShader::loadFloat(location_numberOfRows, numberOfRows);
}

void StaticShader::loadSkyColour(float r, float g, float b) {
	StaticShader::load3DVector(location_skyColour, glm::vec3(r, g, b));
}

void StaticShader::loadFakeLightingVariable(bool useFake) {
	StaticShader::loadBoolean(location_useFakeLighting, useFake);
}
void StaticShader::loadShineVariables(float damper, float reflectivity) {
	StaticShader::loadFloat(location_shineDamper, damper);
	StaticShader::loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
	//cout << "Now static shader::loadTransformationMatrix was called with the location of " << location_transformationMatrix << endl;
	StaticShader::loadMatrix(location_transformationMatrix, matrix);

}

void StaticShader::loadProjectionMatrix(glm::mat4 projection) {
	StaticShader::loadMatrix(location_projectionMatrix, projection);
}

void StaticShader::loadLights(std::vector<Light> lights) {
	for (int i = 0; i<MAX_LIGHTS; i++) {
		if (i<lights.size()) {
			StaticShader::load3DVector(location_lightPosition[i], lights[i].getPosition());
			StaticShader::load3DVector(location_lightColour[i], lights[i].getColour());
			StaticShader::load3DVector(location_attenuation[i], lights[i].getAttenuation());
		}
		else {
			//The following calculations have to be included so the shader doesnt divide by zero...
			//So... basically this always loads for 4 lights even if there isnt 4 lights around
			//whenever there is only 1 light, for example, this will then load 3 blank lights to fill in the last 3 spots...
			StaticShader::load3DVector(location_lightPosition[i], glm::vec3(0, 0, 0));
			StaticShader::load3DVector(location_lightColour[i], glm::vec3(0, 0, 0));
			StaticShader::load3DVector(location_attenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void StaticShader::loadViewMatrix(glm::mat4 viewMatrix) {
	//Maths math;
	//glm::mat4 viewMatrix = createViewMatrix(camera); // = math.createViewMatrix(camera);
													 //createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
	
}
/*
//Note: this doesnt use "Roll" because it wasnt used in the tutorial. 
glm::mat4 StaticShader::createViewMatrix(Camera* camera) {

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

	//The parameters for the following function are as follows: cameraPosition, cameraTarget, and upVector
	//The cameraPosition is simply the position of the camera, this is found with camera.getPosition()
	//The camera target is basically where you want the camera to point. for now we set it to 0,0,0
	//The upVector is a static variable for now - indicates how much you look up. 
	//glm::mat4 viewMatrix = glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getcameraFront(), camera.getcameraUp());
	/*
	std::cout << "The following is the contents of the viewMatrix" << std::endl;
	std::cout << "viewMatrix[0][0] = " << viewMatrix[0][0] << std::endl;
	std::cout << "viewMatrix[0][1] = " << viewMatrix[0][1] << std::endl;
	std::cout << "viewMatrix[0][2] = " << viewMatrix[0][2] << std::endl;
	std::cout << "viewMatrix[0][3] = " << viewMatrix[0][3] << std::endl;
	std::cout << "viewMatrix[1][0] = " << viewMatrix[1][0] << std::endl;
	std::cout << "viewMatrix[1][1] = " << viewMatrix[1][1] << std::endl;
	std::cout << "viewMatrix[1][2] = " << viewMatrix[1][2] << std::endl;
	std::cout << "viewMatrix[1][3] = " << viewMatrix[1][3] << std::endl;
	std::cout << "viewMatrix[2][0] = " << viewMatrix[2][0] << std::endl;
	std::cout << "viewMatrix[2][1] = " << viewMatrix[2][1] << std::endl;
	std::cout << "viewMatrix[2][2] = " << viewMatrix[2][2] << std::endl;
	std::cout << "viewMatrix[2][3] = " << viewMatrix[2][3] << std::endl;
	std::cout << "viewMatrix[3][0] = " << viewMatrix[3][0] << std::endl;
	std::cout << "viewMatrix[3][1] = " << viewMatrix[3][1] << std::endl;
	std::cout << "viewMatrix[3][2] = " << viewMatrix[3][2] << std::endl;
	std::cout << "viewMatrix[3][3] = " << viewMatrix[3][3] << std::endl;
	
}*/