#include "FontShader.h"

getPaths fontFsVsLocations;
const std::string FontShader::VERTEX_FILE = fontFsVsLocations.GetCurrentWorkingDir() + "\\fontVertex.txt";
const std::string FontShader::FRAGMENT_FILE = fontFsVsLocations.GetCurrentWorkingDir() + "\\fontFragment.txt";

void FontShader::fontShaders() {
	ShaderProgram(VERTEX_FILE, FRAGMENT_FILE);
	bindAttributes();
	getAllUniformLocations();
}
void FontShader::bindAttributes() {
	FontShader::bindAttribute(0, "position");
	FontShader::bindAttribute(1, "textureCoords");
}
void FontShader::getAllUniformLocations() {
	location_colour = FontShader::getUniformLocation("colour");
	location_translation = FontShader::getUniformLocation("translation");
	location_width = FontShader::getUniformLocation("width");
	location_edge = FontShader::getUniformLocation("edge");
	location_borderWidth = FontShader::getUniformLocation("borderWidth");
	location_borderEdge = FontShader::getUniformLocation("borderEdge");
	location_borderColour = FontShader::getUniformLocation("borderColour");
	location_offset = FontShader::getUniformLocation("offset");
}
void FontShader::loadColour(glm::vec3 colour) {
	FontShader::load3DVector(location_colour, colour);
}
void FontShader::loadTranslation(glm::vec2 translation) {
	FontShader::load2DVector(location_translation, translation);
}

void FontShader::loadWidth(float width) {
	FontShader::loadFloat(location_width, width);
}

void FontShader::loadEdge(float edge) {
	FontShader::loadFloat(location_edge, edge);
}

void FontShader::loadBorderWidth(float borderWidth) {
	FontShader::loadFloat(location_borderWidth, borderWidth);
}

void FontShader::loadBorderEdge(float borderEdge) {
	FontShader::loadFloat(location_borderEdge, borderEdge);
}

void FontShader::loadBorderColour(glm::vec3 borderColour) {
	FontShader::load3DVector(location_borderColour, borderColour);
}

void FontShader::loadOffset(glm::vec2 offset) {
	FontShader::load2DVector(location_offset, offset);
}