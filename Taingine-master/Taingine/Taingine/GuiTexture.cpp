#include "GuiTexture.h"


GuiTexture::GuiTexture(int textures, glm::vec2 positions, glm::vec2 scales) {
	texture = textures;
	position = positions;
	scale = scales;
}

int GuiTexture::getTexture() {
	return texture;
}
glm::vec2 GuiTexture::getPosition() {
	return position;
}
glm::vec2 GuiTexture::getScale() {
	return scale;
}

GuiTexture::~GuiTexture(void)
{
}
