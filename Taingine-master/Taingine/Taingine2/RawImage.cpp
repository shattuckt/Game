#include "RawImage.h"
//RawImage::RawImage(unsigned char* image, int width, int height) {
RawImage::RawImage(GLFWimage image) {
	//this->image = image;
	//this->width = width;
	//this->height = height;
	this->image = image;

}
GLFWimage RawImage::getImage() {
	return image;
}

RawImage RawImage::load(std::string filePath) {
	//int width, height, nrChannels;
	//unsigned char* texture = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	GLFWimage image; 
	image.pixels = stbi_load(filePath.c_str(), &image.width, &image.height, 0, 4);
	//rgba channels glfwSetWindowIcon(window, 1, images); stbi_image_free(images[0].pixels); 
	std::cout << " RawImage details: \n   Path = " << filePath <<
		"\n    Height = " << image.height <<
		"\n    Width =  " << image.width << std::endl;

	if (image.pixels) {
		//return RawImage(image.pixels, image.width, image.height);
		return RawImage(image);
	}
	else {
		//maybe add some sort of global error messaging later on
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(image.pixels);
		exit(EXIT_FAILURE);
	}

}