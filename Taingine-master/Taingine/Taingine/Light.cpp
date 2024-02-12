#include "Light.h"


Light::Light(glm::vec3 positions, glm::vec3 colours) {
	position = positions;
	colour = colours;
	attenuation = glm::vec3(1, 0, 0); //by default, there will be no attenuation
}

Light::Light(glm::vec3 positions, glm::vec3 colours, glm::vec3 attenuations) {
	position = positions;
	colour = colours;
	attenuation = attenuations; //This is used for objects that do require attenuation
}

glm::vec3 Light::getPosition() {
	return position;
}
glm::vec3 Light::getColour() {
	return colour;
}
glm::vec3 Light::getAttenuation() {
	return attenuation;
}
void Light::setPosition(glm::vec3 positions) {
	position = positions;
}
void Light::setColour(glm::vec3 colours) {
	colour = colours;
}

Light::~Light(void)
{
}
