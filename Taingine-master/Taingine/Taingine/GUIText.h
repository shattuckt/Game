#pragma once
#include <glm-0.9.8.5/glm/glm.hpp>
#include <iostream>
#include "FontType.h"

//This class represents a piece of text in the game

class TextMeshCreator;
class FontType;

class GUIText
{
private:
	std::string textString;    // the text.
	float fontSize;            // the font size of the text, where a font size of 1 is the default size.

	int textMeshVao;
	int vertexCount;
	glm::vec3 colour;
	float width;
	float edge;

	//the following are all special effect vars
	float borderWidth;
	float borderEdge;
	glm::vec3 borderColour;
	glm::vec2 offset;

	glm::vec2 position;        // the position on the screen where the top left corner of the text should be rendered.The top left corner of the screen is (0, 0) and the bottom right is(1, 1).
	float lineMaxSize;         // basically the width of the virtual page in terms of screen width(1 is full screen width, 0.5 is half the width of the screen, etc.) Text cannot go off the edge of the page, so if
									// the text is longer than this length it will go onto the next line.When text is centered it is centered into the middle of the line, based on this line length value.
	int numberOfLines;

	FontType* font;             // the font that this text should use.

	bool centerText = false;   // whether the text should be centered or not.

public:
#pragma region void remove()
	/// text - a string of text you want rendered on the screen
	/// fontsize - how large the text is
	/// font - the type of font used 
	/// where on the screen it needs to be rendered (remember 2d here) (0-1,0-1)
	///			ex: glm::vec2(0.5f, 0.5f) would be bottom right portion of screen.
	/// maxLineLength - the length of the virtual text area before text is wrapped 1 = whole screen (so between 0 and 1)
	/// centered - shoudl the text be centered?
	GUIText(std::string text, float fontSize, FontType* font, glm::vec2 position, float maxLineLength, bool centered);
	GUIText(void) {};
#pragma endregion

#pragma region void remove()
	/// Remove the text from the screen.
	void remove();
#pragma endregion

#pragma region FontType* getFont()
	/// return The font used by this text.
	FontType* getFont();
#pragma endregion

#pragma region void setColour(float r, float g, float b)
	/// Set the colour of the text.
	/// r - red value, between 0 and 1.
	/// g - green value, between 0 and 1.
	/// b - blue value, between 0 and 1.
	void setColour(float r, float g, float b);
#pragma endregion

#pragma region glm::vec3 getColour()
	/// return the colour of the text.
	glm::vec3 getColour();
#pragma endregion

#pragma region void setBorderColour(float r, float g, float b)
	/// Set the colour of the text.
	/// r - red value, between 0 and 1.
	/// g - green value, between 0 and 1.
	/// b - blue value, between 0 and 1.
	void setBorderColour(float r, float g, float b);
#pragma endregion

#pragma region glm::vec3 getBorderColour()
	/// return the colour of the text.
	glm::vec3 getBorderColour();
#pragma endregion

#pragma region void setOffset(float x, float y)
	/// Set the colour of the text.
	/// x and y coordinates for offset
	void setOffset(float x, float y);
#pragma endregion

#pragma region glm::vec2 getOffset()
	/// return the colour of the text.
	glm::vec2 getOffset();
#pragma endregion

#pragma region void setWidth(float width);
	/// Set the character's width (from center of text's center line)
	void setWidth(float width);
#pragma endregion

#pragma region float getWidth()
	/// return the width of the text.
	float getWidth();
#pragma endregion

#pragma region void setEdge(float edge);
	/// Set the character's edge (from center of text's center line)
	void setEdge(float edge);
#pragma endregion

#pragma region float getEdge()
	/// return the edge of the text.
	float getEdge();
#pragma endregion

#pragma region void setBorderWidth(float borderWidth);
	/// Set the character's width (from center of text's center line)
	void setBorderWidth(float borderWidth);
#pragma endregion

#pragma region float getBorderWidth()
	/// return the width of the text.
	float getBorderWidth();
#pragma endregion

#pragma region void setBorderEdge(float borderEdge);
	/// Set the character's edge (from center of text's center line)
	void setBorderEdge(float borderEdge);
#pragma endregion

#pragma region float getBorderEdge()
	/// return the edge of the text.
	float getBorderEdge();
#pragma endregion

#pragma region int getNumberOfLines()
	/// return The number of lines of text. This is determined when the text is loaded, based on the length of the textand the max line length that is set.
	int getNumberOfLines();
#pragma endregion

#pragma region glm::vec2 getPosition()
	/// return The position of the top-left corner of the text in screen-space. (0, 0) is the top left corner of the screen, (1, 1) is the bottom right.
	glm::vec2 getPosition();
#pragma endregion

#pragma region int getMesh()
	/// return the ID of the text's VAO, which contains all the vertex data for the quads on which the text will be rendered.
	int getMesh();
#pragma endregion

#pragma region void setMeshInfo(int vao, int verticesCount)
	/// Set the VAO and vertex count for this text.
	/// param vao - the VAO containing all the vertex data for the quads on which the text will be rendered.
	/// param verticesCount - the total number of vertices in all of the quads.
	void setMeshInfo(int vao, int verticesCount);
#pragma endregion

#pragma region int getVertexCount()
	/// return The total number of vertices of all the text's quads.
	int getVertexCount();
#pragma endregion

#pragma region float getFontSize()
	/// return the font size of the text (a font size of 1 is normal).
	float getFontSize();
#pragma endregion

#pragma region void setNumberOfLines(int number)
	/// Sets the number of lines that this text covers (method used only in loading).
	/// param number
	void setNumberOfLines(int number);
#pragma endregion

#pragma region bool isCentered()
	/// return {@code true} if the text should be centered.
	bool isCentered();
#pragma endregion

#pragma region float getMaxLineSize()
	/// return The maximum length of a line of this text.
	float getMaxLineSize();
#pragma endregion

#pragma region std::string getTextString()
	/// return The maximum length of a line of this text.
	std::string getTextString();
#pragma endregion


};

