#include "Entity.h"

Entity::Entity(TexturedModel model, int index, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
{
	this->textureIndex = index;
	this->model = model;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}
Entity::Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
{
	this->textureIndex = NULL;
	this->model = model;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}
Entity::Entity()
{
	this->textureIndex = NULL;
	this->model = TexturedModel();
	this->position = glm::vec3(NULL,NULL,NULL);
	this->rotX = NULL;
	this->rotY = NULL;
	this->rotZ = NULL;
	this->scale = NULL;
}

//The following two functions are to find the offset for the different textures (if any) contained in the single texture file
//This assumes they are in a matrix grid, so 4 textures in a 2x2 matrix or 9 textures in a 3x3 matrix..etc.. 
//Just like before, the offset starts from the top left of the texture. (0,0) would be the top left texture. (maxX, maxY) would be the bottom right texture. 
float Entity::getTextureXOffset() {
	int column = textureIndex % model.getTexture().getNumberofRows();
	return (float)column / (float)model.getTexture().getNumberofRows();
}

float Entity::getTextureYOffset() {
	int row = textureIndex / model.getTexture().getNumberofRows();
	return (float)row / (float)model.getTexture().getNumberofRows();
}

void Entity::increasePosition(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}

void Entity::setModel(TexturedModel model) {
	this->model = model;
}
void Entity::setPosition(glm::vec3 position) {
	this->position = position;
}
void Entity::setRotX(float rotX) {
	this->rotX = rotX;
}
void Entity::setRotY(float rotY) {
	this->rotY = rotY;
}
void Entity::setRotZ(float rotZ) {
	this->rotZ = rotZ;
};
void Entity::setScale(float scale) {
	this->scale = scale;
}
TexturedModel Entity::getModel() {
	return model;
}
glm::vec3 Entity::getPosition() {
	return position;
}
float Entity::getRotX() {
	return rotX;
}
float Entity::getRotY() {
	return rotY;
}
float Entity::getRotZ() {
	return rotZ;
}
float Entity::getScale() {
	return scale;
}
float Entity::getTextureIndex() {
	return textureIndex;
}
Entity::~Entity(void){
}
