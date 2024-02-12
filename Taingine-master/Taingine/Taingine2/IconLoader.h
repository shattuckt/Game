#pragma once
#include <iostream>
#include <vector>
#include <filesystem>

#include "GetWorkingDirectory.h"

#include "RawImage.h"

class IconLoader{
private:
	static std::vector<GLFWimage> images;
public:
	static std::vector<GLFWimage> loadIcon(std::vector<std::string> filePaths);
	static GLFWimage loadGlfwImage(std::string filePath);
};

