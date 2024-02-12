#include "IconLoader.h"
std::vector<GLFWimage> IconLoader::images;
std::vector<GLFWimage> IconLoader::loadIcon(std::vector<std::string> filePaths) {
	for (int i = 0; i < filePaths.size(); i++) {
		try {
			images.push_back(loadGlfwImage(filePaths[i]));
		}
		catch (int e) {
			std::cout << "Unable to load icon - " << filePaths[i] << " Error: " << e << std::endl;
			break;
		}
	}
	return images;
}

GLFWimage IconLoader::loadGlfwImage(std::string filePath) {
	return RawImage::load(filePath).getImage();
}