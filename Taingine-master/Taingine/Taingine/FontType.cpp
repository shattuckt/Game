#include "FontType.h"

FontType::FontType(int textureAtlas, std::string fontFile, DisplayManager* display) {
	this->textureAtlas = textureAtlas;
	this->display = display;
	this->textMeshCreator = new TextMeshCreator(fontFile, display);
}
int FontType::getTextureAtlas() {
	return textureAtlas;
}
TextMeshData* FontType::loadText(GUIText* text) {
	return textMeshCreator->createTextMesh(text);
}