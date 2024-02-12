#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
//#include <filesystem>

#include "GetWorkingDirectory.h"

#include "stb_image.h"


class RawImage{
private:
	//unsigned char* image;
	//int width;
	//int height;
	GLFWimage image;
	RawImage(GLFWimage image);
public:
	GLFWimage getImage();

	static RawImage load(std::string filePath);
};

