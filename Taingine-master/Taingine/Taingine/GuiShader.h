#pragma once
#include "ShaderProgram.h"
#include "getPaths.h"

class GuiShader : public ShaderProgram
{
private:
	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	unsigned int location_transformationMatrix;

public:

	GuiShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

	void GuiShaders();
	void bindAttributes();
	void getAllUniformLocations();

	void loadTransformation(glm::mat4 matrix);

	~GuiShader(void);
};

