#include "ModelTexture.h"


ModelTexture::ModelTexture(int texture) {

	textureID = texture;
	normalMap = -1;
	shineDamper = 1; //default usually is 1
	reflectivity = 0; //default usually is 0
	hasTransparency = false; //default is false
	useFakeLighting = false;
	numberOfRows = 1;

}
ModelTexture::ModelTexture(int texture, int normalMapID) {
	textureID = texture;
	normalMap = normalMapID;
	shineDamper = 1;
	reflectivity = 0;
	hasTransparency = false;
	useFakeLighting = false;
	numberOfRows = 1;
}
ModelTexture::ModelTexture() {
	textureID = -1;
	normalMap = -1;
	shineDamper = 1;
	reflectivity = 0;
	hasTransparency = false;
	useFakeLighting = false;
	numberOfRows = 1;
}

float ModelTexture::getShineDamper() {
	return shineDamper;
}
float ModelTexture::getReflectivity() {
	return reflectivity;
}
bool ModelTexture::getHasTransparency() {
	return hasTransparency;
}
bool ModelTexture::getuseFakeLighting() {
	return useFakeLighting;
}
int ModelTexture::getNumberofRows() {
	return numberOfRows;
}
void ModelTexture::setNumberOfRows(int numberOfRow) {
	numberOfRows = numberOfRow;
}
int ModelTexture::getNormalMap() {
	return normalMap;
}
void ModelTexture::setNormalMap(int normalMaps) {
	normalMap = normalMaps;
}
void ModelTexture::setShineDamper(float shineDampers) {
	shineDamper = shineDampers;
}
void ModelTexture::setReflectivity(float reflectivitys) {
	reflectivity = reflectivitys;
}
void ModelTexture::setHasTransparency(bool hasTransparencys) {
	hasTransparency = hasTransparencys;
}
void ModelTexture::setuseFakeLighting(bool useFakeLightings) {
	useFakeLighting = useFakeLightings;
}
int ModelTexture::getID() {

	return textureID;

}

ModelTexture::~ModelTexture(void)
{
}
