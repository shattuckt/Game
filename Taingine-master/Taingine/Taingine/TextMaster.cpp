#include "TextMaster.h"

void TextMaster::init(Loader loader, DisplayManager* display) {
	this->renderer = new FontRenderer(display);
	this->loader = loader;
}

void TextMaster::render() {
	renderer->render(texts);
}

void TextMaster::loadText(GUIText* text) {
	FontType* font = text->getFont();
	TextMeshData* data = font->loadText(text);
	//std::cout << "textMeshData sizes - vertexPos = " << data->getVertexPositions().size() <<
		//"\ntextreCords = " << data->getTextureCoords().size() << std::endl;
	int vao = loader.loadToVAO(data->getVertexPositions(), data->getTextureCoords());
	text->setMeshInfo(vao, data->getVertexCount());

	texts[font].push_back(text);
	std::vector<GUIText*> textBatch = texts[font];
	//std::cout << "TextBatch size (TextMaster line13) = " << textBatch.size() << std::endl;

}

void TextMaster::removeText(GUIText* text) {
	texts[text->getFont()].clear();
}
void TextMaster::cleanUp() {
	renderer->cleanUp();
}