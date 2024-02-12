#pragma once
#include "getPaths.h"
#include "ShaderProgram.h"

class ParticleShader : public ShaderProgram
{
private:
	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	int location_numberOfRows;
	int location_projectionMatrix;
	int location_viewMatrix;

public:
	ParticleShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}
	void fontShaders();
	void bindAttributes();
	void getAllUniformLocations();

	void loadNumberOfRows(float numberOfRows);

	void loadProjectionMatrix(glm::mat4 projectionMatrix);

	void loadViewMatrix(glm::mat4 viewMatrix);
};