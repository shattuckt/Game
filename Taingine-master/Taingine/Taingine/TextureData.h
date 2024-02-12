#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

class TextureData
{
private:
	int width;
	int height;
	GLenum format;
	//const void *voidTexture;
	std::vector<unsigned char> texture;

public:
	TextureData(unsigned char *textures, int widths, int heights, GLenum formats, int nrChannels);

	std::vector<unsigned char> getTexture();
	int getWidth();
	int getHeight();
	GLenum getFormat();

	~TextureData(void);
};

