#include "GuiRenderer.h"



GuiRenderer::GuiRenderer(Loader loader) {
	float holdPositions[8] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f }; //This is just the coords for a quad.
	std::vector<float> positions(holdPositions, holdPositions + sizeof(holdPositions) / sizeof(holdPositions[0])); //Convert it to a vector because arrays suck
	quad = loader.loadToVAO(positions, 2); //store the quad into a vao

	GuiShader shader;
	shader.GuiShaders();
	shaders = shader;




}

void GuiRenderer::render(std::vector<GuiTexture> guis) {
	shaders.start();
	glBindVertexArray(quad.get_VaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND); //this will blend the alpha values to enable transparency (NOTE ONLY USE THIS FOR GUIS)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST); //prevents guis that are below another from not getting rendered. so this enables overlapping gui textures. 
	for (unsigned int x = 0; x < guis.size(); x = x + 1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, guis[x].getTexture());
		Maths math;
		glm::mat4 transformationMatrix = math.createTransformationMatrix(guis[x].getPosition(), guis[x].getScale());
		shaders.loadTransformation(transformationMatrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.get_VertexCount());

	}
	glEnable(GL_DEPTH_TEST); //re-enable the depth test attribute once the gui's have been rendered
	glDisable(GL_BLEND); //disable blending as it is not good for anything outside of the gui textures. 
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shaders.stop();
}

void GuiRenderer::cleanUp() {
	shaders.cleanUp();
}

GuiRenderer::~GuiRenderer(void)
{
}
