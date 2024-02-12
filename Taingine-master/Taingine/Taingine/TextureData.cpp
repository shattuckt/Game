#include "TextureData.h"


TextureData::TextureData(unsigned char *textures, int widths, int heights, GLenum formats, int nrChannels) {

	width = widths;
	height = heights;
	format = formats;
	//try initiliazling the vector here and then freeing the stbi image... 
	//texture = textures;
	texture.assign(textures, textures + (width * height * nrChannels));
	stbi_image_free(textures);

}

std::vector<unsigned char> TextureData::getTexture() {
	return texture;
}
int TextureData::getWidth() {
	return width;
}
int TextureData::getHeight() {
	return height;
}
GLenum TextureData::getFormat() {
	return format;
}


TextureData::~TextureData(void) {}
