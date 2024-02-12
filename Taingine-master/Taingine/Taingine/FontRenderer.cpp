#include "FontRenderer.h"

FontRenderer::FontRenderer(DisplayManager* display) {
	this->shader = new FontShader();
	shader->fontShaders();
	this->display = display;
}

void FontRenderer::render(std::unordered_map<FontType*, std::vector<GUIText*>, hash_textMap, equal_textMap> texts) {
	prepare();
	for (std::unordered_map<FontType*, std::vector<GUIText*>, hash_textMap, equal_textMap>::iterator it = texts.begin(); it != texts.end(); ++it) {

		//std::cout << "second's texture atlas " << it->second[0]->getFont()->getTextureAtlas() << std::endl;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, it->second[0]->getFont()->getTextureAtlas());

		std::vector<GUIText*> textBatch = texts.at(it->first);
		//At this point we have batch holding each entity within that key (model type)
		//So we need to loop through each entity affiliated with the TexturedModel type.. any amount of stall.obj for example 
		for (int x = 0; x < textBatch.size(); x++) {
			renderText(textBatch[x]);
		}
	}
}

void FontRenderer::cleanUp() {
	shader->cleanUp();
}
void FontRenderer::prepare() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	shader->start();
}
void FontRenderer::renderText(GUIText* text) {
	glBindVertexArray(text->getMesh());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	shader->loadColour(text->getColour());
	shader->loadTranslation(text->getPosition());
	shader->loadWidth(text->getWidth());
	shader->loadEdge(text->getEdge());
	shader->loadBorderWidth(text->getBorderWidth());
	shader->loadBorderEdge(text->getBorderEdge());
	shader->loadBorderColour(text->getBorderColour());
	shader->loadOffset(text->getOffset());
	glDrawArrays(GL_TRIANGLES, 0, text->getVertexCount());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}
void FontRenderer::endRendering() {
	shader->stop();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
