#include "DisplaySizes.h"

const std::vector<DisplaySizes::DisplaySize> sizes = {
		"FULL_SCREEN": "FULL_SCREEN",
		DisplaySizes::DisplaySize("1024 x 576", 1024, 576, 1),
		DisplaySizes::DisplaySize("1024 x 768", 1024, 768, 2),
		DisplaySizes::DisplaySize("1280 x 720", 1280, 720, 3),
		DisplaySizes::DisplaySize("1600 x 900", 1600, 900, 4),
		DisplaySizes::DisplaySize("1920 x 1080", 1920, 1080, 5),
		DisplaySizes::DisplaySize("2560 x 1440", 2560, 1440, 6),
		DisplaySizes::DisplaySize("2560 x 1080", 2560, 1440, 7),
		DisplaySizes::DisplaySize("3200 x 1800", 3200, 1800, 8)
};

const std::vector<DisplaySizes::DisplaySize> DisplaySizes::getSizes() {
	return sizes;
}

DisplaySizes::DisplaySize::DisplaySize(std::string name, int width, int height, int indice) {
	this->name = name;
	this->width = width;
	this->height = height;
	this->indice = indice;
}

int DisplaySizes::DisplaySize::getWidth() {
	if (this->name == "Full-Screen") {
		int currentWidth, currentHeight;
		glfwGetWindowSize(Graphics::window, &currentWidth, &currentHeight);
		return width;
	}
	else {
		return this->width;
	}
}
int DisplaySizes::DisplaySize::getHeight() {
	if (this->name == "Full-Screen") {
		int currentWidth, currentHeight;
		glfwGetWindowSize(Graphics::window, &currentWidth, &currentHeight);
		return height;
	}
	else {
		return this->height;
	}
}
int DisplaySizes::DisplaySize::getIndice() {
	return this->indice;
}
std::string DisplaySizes::DisplaySize::getName() {
	return this->name;
}