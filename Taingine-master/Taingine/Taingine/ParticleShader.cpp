#include "ParticleShader.h"

getPaths particleFsVsLocations;
const std::string ParticleShader::VERTEX_FILE = particleFsVsLocations.GetCurrentWorkingDir() + "\\particleVShader.txt";
const std::string ParticleShader::FRAGMENT_FILE = particleFsVsLocations.GetCurrentWorkingDir() + "\\particleFShader.txt";

void ParticleShader::fontShaders() {
	ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);
	bindAttributes();
	getAllUniformLocations();
}

void ParticleShader::bindAttributes() {
	ParticleShader::bindAttribute(0, "position");
	ParticleShader::bindAttribute(1, "vertexPosition");
	ParticleShader::bindAttribute(2, "scale");
	ParticleShader::bindAttribute(3, "texOffsets");
	ParticleShader::bindAttribute(4, "blendFactor");
}

void ParticleShader::getAllUniformLocations() {
	location_numberOfRows = ParticleShader::getUniformLocation("numberOfRows");
	location_projectionMatrix = ParticleShader::getUniformLocation("projectionMatrix");
	location_viewMatrix = ParticleShader::getUniformLocation("viewMatrix");
}

void ParticleShader::loadNumberOfRows(float numberOfRows) {
	ParticleShader::loadFloat(location_numberOfRows, numberOfRows);
}

void ParticleShader::loadProjectionMatrix(glm::mat4 projectionMatrix) {
	ParticleShader::loadMatrix(location_projectionMatrix, projectionMatrix);
}

void ParticleShader::loadViewMatrix(glm::mat4 viewMatrix) {
	ParticleShader::loadMatrix(location_viewMatrix, viewMatrix);
}