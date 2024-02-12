#include "ShaderProgram.h"

//ShaderProgram::ShaderProgram() {}

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile) {

	std::cout << "About to create shader using vertex: " << vertexFile << std::endl;
	std::cout << "and fragment: " << fragmentFile << std::endl;
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	//bindAttributes();
	glLinkProgram(programID);
	//glValidateProgram(programID);

	//testing the link
	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(programID, 1024, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "PROGRAM" << infoLog << "\n-- --------------------------------------------------- -- " << std::endl;
	}

	//getAllUniformLocations();

}



int ShaderProgram::getUniformLocation(string uniformName) {
	return glGetUniformLocation(programID, uniformName.c_str());

}

void ShaderProgram::start() {
	glUseProgram(programID);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::cleanUp() {

	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, vertexShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);

	cout << "Shader loaded successfully " << endl;

}

void ShaderProgram::bindAttribute(int attribute, string variableName) { //had to mess with the glchar, not sure if thats right or not... 

	const char *varName = variableName.c_str();
	glBindAttribLocation(programID, attribute, varName);

}

void ShaderProgram::loadFloat(int location, float value) {
	glUniform1f(location, value);
}
void ShaderProgram::loadInt(int location, int value) {
	glUniform1i(location, value);
}

void ShaderProgram::load4DVector(int location, glm::vec4 vector) { //loads 4D vectors.. 
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::load3DVector(int location, glm::vec3 vector) { //loads 3D vectors.. 
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::load2DVector(int location, glm::vec2 vector) {
	glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::loadBoolean(int location, bool value) {
	float toLoad = 0;
	if (value) {
		toLoad = 1;
	}
	glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(unsigned long int location, glm::mat4 matrix) {
	//std::cout << "StaticShader called ShaderProgram::loadMatrix and the matrix has the location of " << location << std::endl;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));  //takes in the location, how many matrices we want to send, do we want to transpose, and matrix data (GL will only accept these transformed values
}

int ShaderProgram::loadShader(string file, int type) {

	// 1. retrieve the vertex/fragment source code from filePath
	std::string shader;

	std::ifstream File;

	const char* shaderSource;

	//for the compile checker
	GLint isCompiled = 0;

	// ensure ifstream objects can throw exceptions:
	File.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		File.open(file);

		std::stringstream FileStream;
		// read file's buffer contents into streams
		FileStream << File.rdbuf();

		// close file handlers
		File.close();

		// convert stream into string
		shader = FileStream.str();

		// convert again? seems bad
		shaderSource = shader.c_str();


	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	int shaderID = glCreateShader(type);

	glShaderSource(shaderID, 1, &shaderSource, NULL);  //not sure this will work... supposed to be glShaderSource(shaderID, shaderSource);

	glCompileShader(shaderID);  //is this the correct spot for this?

								//The following will tell you if the compilation was successful 
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) {

		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- ---------------------------------------------------- -- " << std::endl;


	}

	return shaderID;

}