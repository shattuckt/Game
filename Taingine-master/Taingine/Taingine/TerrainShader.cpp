#include "TerrainShader.h"

const int MAX_LIGHTS = 4;

getPaths getPathss;
const std::string TerrainShader::VERTEX_FILE = getPathss.GetCurrentWorkingDir() + "\\terrainVertexShader.txt";
const std::string TerrainShader::FRAGMENT_FILE = getPathss.GetCurrentWorkingDir() + "\\terrainFragmentShader.txt";



void TerrainShader::TerrainShaders() {
	TerrainShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);
	TerrainShader::bindAttributes();
	TerrainShader::getAllUniformLocations();
}

void TerrainShader::bindAttributes() {  //bind all the attributes needed for the shader..
	TerrainShader::bindAttribute(0, "position");
	TerrainShader::bindAttribute(1, "textureCoordinates");
	TerrainShader::bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations() { //get all the locations needed for the shader...
	location_transformationMatrix = TerrainShader::getUniformLocation("transformationMatrix");
	location_projectionMatrix = TerrainShader::getUniformLocation("projectionMatrix");
	location_viewMatrix = TerrainShader::getUniformLocation("viewMatrix");
	//location_lightPosition = TerrainShader::getUniformLocation("lightPosition");
	//location_lightColour = TerrainShader::getUniformLocation("lightColour");
	location_shineDamper = TerrainShader::getUniformLocation("shineDamper");
	location_reflectivity = TerrainShader::getUniformLocation("reflectivity");
	location_skyColour = TerrainShader::getUniformLocation("skyColour");
	location_backgroundTexture = TerrainShader::getUniformLocation("backgroundTexture");
	location_rTexture = TerrainShader::getUniformLocation("rTexture");
	location_gTexture = TerrainShader::getUniformLocation("gTexture");
	location_bTexture = TerrainShader::getUniformLocation("bTexture");
	location_blendMap = TerrainShader::getUniformLocation("blendMap");
	location_plane = TerrainShader::getUniformLocation("plane");

	for (int i = 0; i<MAX_LIGHTS; i++) {
		location_lightPosition.push_back(TerrainShader::getUniformLocation("lightPosition[" + std::to_string(static_cast<long long>(i)) + "]"));
		location_lightColour.push_back(TerrainShader::getUniformLocation("lightColour[" + std::to_string(static_cast<long long>(i)) + "]"));
		location_attenuation.push_back(TerrainShader::getUniformLocation("attenuation[" + std::to_string(static_cast<long long>(i)) + "]"));
		//std::cout << "location_lightPos[" << i << "] is equal to " << StaticShader::getUniformLocation("lightPosition[" + std::to_string(static_cast<long long>(i)) + "]") << std::endl;
		//std::cout << "location_lightColour[" << i << "] is equal to " << StaticShader::getUniformLocation("lightColour[" + std::to_string(static_cast<long long>(i)) + "]") << std::endl;
	}


}

void TerrainShader::connectTextureUnits() {
	TerrainShader::loadInt(location_backgroundTexture, 0);
	TerrainShader::loadInt(location_rTexture, 1);
	TerrainShader::loadInt(location_gTexture, 2);
	TerrainShader::loadInt(location_bTexture, 3);
	TerrainShader::loadInt(location_blendMap, 4);
}

void TerrainShader::loadClipPlane(glm::vec4 clipPlane) {
	TerrainShader::load4DVector(location_plane, clipPlane);
}

void TerrainShader::loadSkyColour(float r, float g, float b) {
	TerrainShader::load3DVector(location_skyColour, glm::vec3(r, g, b));
}

void TerrainShader::loadShineVariables(float damper, float reflectivity) {
	TerrainShader::loadFloat(location_shineDamper, damper);
	TerrainShader::loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix) {
	//cout << "Now static shader::loadTransformationMatrix was called with the location of " << location_transformationMatrix << endl;
	TerrainShader::loadMatrix(location_transformationMatrix, matrix);

}

void TerrainShader::loadProjectionMatrix(glm::mat4 projection) {
	TerrainShader::loadMatrix(location_projectionMatrix, projection);
}

void TerrainShader::loadLights(std::vector<Light> lights) {
	for (int i = 0; i<MAX_LIGHTS; i++) {
		if (i<lights.size()) {
			TerrainShader::load3DVector(location_lightPosition[i], lights[i].getPosition());
			TerrainShader::load3DVector(location_lightColour[i], lights[i].getColour());
			TerrainShader::load3DVector(location_attenuation[i], lights[i].getAttenuation());
		}
		else {
			//The following calculations have to be included so the shader doesnt divide by zero...
			//So... basically this always loads for 4 lights even if there isnt 4 lights around
			//whenever there is only 1 light, for example, this will then load 3 blank lights to fill in the last 3 spots...
			TerrainShader::load3DVector(location_lightPosition[i], glm::vec3(0, 0, 0));
			TerrainShader::load3DVector(location_lightColour[i], glm::vec3(0, 0, 0));
			TerrainShader::load3DVector(location_attenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void TerrainShader::loadViewMatrix(glm::mat4 viewMatrix) {
	//Maths math;
	//glm::mat4 viewMatrix = createViewMatrix(camera); // = math.createViewMatrix(camera);
													 //createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);


}

//Note: this doesnt use "Roll" because it wasnt used in the tutorial. 
/*glm::mat4 TerrainShader::createViewMatrix(Camera* camera) {

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