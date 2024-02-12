#pragma once
#include <glm-0.9.8.5\glm\glm.hpp>
class GuiTexture
{
private:

	int texture;
	glm::vec2 position;
	glm::vec2 scale;

public:
	GuiTexture(int textures, glm::vec2 positions, glm::vec2 scales);

	int getTexture();
	glm::vec2 getPosition();
	glm::vec2 getScale();

	~GuiTexture(void);
};

