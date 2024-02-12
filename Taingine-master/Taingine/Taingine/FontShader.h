#pragma once
#include "getPaths.h"
#include "ShaderProgram.h"

class FontShader : public ShaderProgram
{
private:

	static const string VERTEX_FILE;
	static const string FRAGMENT_FILE;

	int location_colour;
	int location_translation;
	int location_width;
	int location_edge;
	int location_borderWidth;
	int location_borderEdge;
	int location_borderColour;
	int location_offset;

public:
	FontShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

	void fontShaders();
	void bindAttributes();
	void getAllUniformLocations();
	void loadColour(glm::vec3 colour);
	void loadTranslation(glm::vec2 translation);
	void loadWidth(float width);
	void loadEdge(float edge);
	void loadBorderWidth(float borderWidth);
	void loadBorderEdge(float borderEdge);
	void loadBorderColour(glm::vec3 borderColour);
	void loadOffset(glm::vec2 offset);

};

