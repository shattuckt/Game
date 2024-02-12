#pragma once
#include <glm-0.9.8.5\glm\glm.hpp>
class Light
{
private:
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 attenuation;
public:
	Light(glm::vec3 positions, glm::vec3 colours);
	Light(glm::vec3 positions, glm::vec3 colours, glm::vec3 attenuations);
	glm::vec3 getPosition();
	glm::vec3 getColour();
	glm::vec3 getAttenuation();
	void setPosition(glm::vec3 positions);
	void setColour(glm::vec3 colours);

	~Light(void);
};

