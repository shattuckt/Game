#pragma once
#include <unordered_map>
#include <vector>
#include "DisplayManager.h"
#include "FontType.h"
#include "FontShader.h"

struct hash_textMap { //This is meant to return the hash of all 5 elements 
	size_t operator()(FontType* fontType) const {
		return hash<int>()(fontType->getTextureAtlas());
	}
};

struct equal_textMap { //We now need to find if they are all equal or not... 
	bool operator()(FontType* lhs, FontType* rhs) const {

		return lhs->getTextureAtlas() == rhs->getTextureAtlas();
	}
};

//figure out if the unordered map only exists to allow for multiple fonts.

/*struct hash_textMap { //This is meant to return the hash of all 5 elements 
	size_t operator()(const textMap& textMap) const {
		FontType fontType = textMap.first;
		GUIText guiText = textMap.second;

		return hash<int>()(fontType.getTextureAtlas()) ^ hash<float>()(guiText.getColour().x) ^ hash<float>()(guiText.getColour().y) ^ hash<float>()(guiText.getColour().z) ^
			hash<int>()(guiText.getFont().getTextureAtlas()) ^ hash<float>()(guiText.getFontSize()) ^ hash<float>()(guiText.getMaxLineSize()) ^
			hash<int>()(guiText.getMesh()) ^ hash<int>()(guiText.getNumberOfLines()) ^ hash<float>()(guiText.getPosition().x) ^ hash<float>()(guiText.getPosition().y) ^
			hash<std::string>()(guiText.getTextString()) ^ hash<int>()(guiText.getVertexCount()) ^ hash<bool>()(guiText.isCentered());
	}
};

struct equal_textMap { //We now need to find if they are all equal or not... 
	bool operator()(const textMap& lhs, const textMap& rhs) const {
		FontType leftFontType = lhs.first;
		FontType rightFontType = rhs.first;
		GUIText lefttext = lhs.second;
		GUIText righttext = rhs.second;

		return leftFontType.getTextureAtlas() == rightFontType.getTextureAtlas() && lefttext.getColour().x == righttext.getColour().x &&
			lefttext.getColour().y == righttext.getColour().y && lefttext.getColour().z == righttext.getColour().z &&
			lefttext.getFont().getTextureAtlas() == righttext.getFont().getTextureAtlas() && lefttext.getFontSize() == righttext.getFontSize() &&
			lefttext.getMaxLineSize() == righttext.getMaxLineSize() && lefttext.getMesh() == righttext.getMesh() &&
			lefttext.getNumberOfLines() == righttext.getNumberOfLines() && lefttext.getPosition().x == righttext.getPosition().x &&
			lefttext.getPosition().y == righttext.getPosition().y && lefttext.getTextString() == righttext.getTextString() &&
			lefttext.getVertexCount() == righttext.getVertexCount() && lefttext.isCentered() == righttext.isCentered();
	}
};*/

class FontRenderer
{
private:
	FontShader* shader;
	DisplayManager* display;
public:
	FontRenderer(DisplayManager* display);
	FontRenderer() {};
	void render(std::unordered_map<FontType*, std::vector<GUIText*>, hash_textMap, equal_textMap> texts);
	void cleanUp();

#pragma region void prepare();
	/// glEnable & glBlend - enable alpha blending (same as GUI tutorials)
	/// glDisable - disabling the depth test since the text shouldnt need to hide behind anything
	void prepare();
#pragma endregion

#pragma region 	void renderText(GUIText* text);
	/// Renders a GUIText object
	/// vao's are stored in 0 and 1
	/// shader is loading the color of the text and then the position that it is in.
	void renderText(GUIText* text);
#pragma endregion

#pragma region 	void endRendering();
	/// Stop shader
	/// Then disable the blending we enabled previously
	void endRendering();
#pragma endregion

};
