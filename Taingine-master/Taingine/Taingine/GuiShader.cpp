#include "GuiShader.h"

getPaths getpaths;
const std::string GuiShader::VERTEX_FILE = getpaths.GetCurrentWorkingDir() + "\\guiVertexShader.txt";
const std::string GuiShader::FRAGMENT_FILE = getpaths.GetCurrentWorkingDir() + "\\guiFragmentShader.txt";

void GuiShader::GuiShaders() {

	//std::cout << "about to create shader from " << VERTEX_FILE << " and " << FRAGMENT_FILE << std::endl;	
	GuiShader::ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);

	GuiShader::bindAttributes();
	GuiShader::getAllUniformLocations();

}

void GuiShader::bindAttributes() { //bind all the attributes needed for the shader..
	bindAttribute(0, "position");
}

void GuiShader::getAllUniformLocations() { //get all the locations needed for the shader...
	location_transformationMatrix = getUniformLocation("transformationMatrix");
}

void GuiShader::loadTransformation(glm::mat4 matrix) { //use the location found to load the variable into the shader
	loadMatrix(location_transformationMatrix, matrix);
}




GuiShader::~GuiShader(void)
{
}
