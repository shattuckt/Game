#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm-0.9.8.5\glm\glm.hpp>
#include <glm-0.9.8.5\glm\matrix.hpp>
#include <glm-0.9.8.5\glm\gtc\type_ptr.hpp>


using namespace std;

class ShaderProgram
{
private:

	int programID;
	int vertexShaderID;
	int fragmentShaderID;

public:

	int getUniformLocation(string uniformName);
	void start();
	void stop();
	void cleanUp();
	void bindAttribute(int attribute, string variableName);

	ShaderProgram(string vertexFile, string fragmentFile);

	ShaderProgram(void) {};
	void loadInt(int location, int value);

	void loadFloat(int location, float value);

	void load4DVector(int location, glm::vec4 vector);

	void load3DVector(int location, glm::vec3 vector);

	void load2DVector(int location, glm::vec2 vector);

	void loadBoolean(int location, bool value);

	int loadShader(string file, int type);

	void loadMatrix(unsigned long int location, glm::mat4 matrix);

};

