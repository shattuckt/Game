#include "WaterRenderer.h"

const string DUDV_MAP = "waterDuDvMap.png";
const string NORMAL_MAP = "waterNormalMap.png";
const float WAVE_SPEED = 0.03f;

WaterRenderer::WaterRenderer(Loader loader, WaterShader* shaders, glm::mat4 projectionMatrix, WaterFrameBuffers wFbos, DisplayManager* displays) {
	shader = shaders;
	waterFbos = wFbos;
	display = displays;
	moveFactor = 0;
	dudvTexture = loader.loadTexture(DUDV_MAP, -0.4f);
	normalMap = loader.loadTexture(NORMAL_MAP, -0.4f);
	shader->start();
	shader->connectTextureUnites();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
	setUpVAO(loader);

}

void WaterRenderer::render(std::vector<WaterTile> water, glm::mat4 viewMatrix, glm::vec3 cameraPosition, Light sun) {
	prepareRender(viewMatrix, cameraPosition, sun);

	Maths math;
	for (unsigned int i = 0; i < water.size(); i++) {
		glm::mat4 modelMatrix = math.createTransformationMatrix(glm::vec3(water[i].getX(), water[i].getHeight(), water[i].getZ()), 0, 0, 0, water[i].getTileSize());
		shader->loadModelMatrix(modelMatrix);

		glDrawArrays(GL_TRIANGLES, 0, quad.get_VertexCount());
	}
	unbind();
}

void WaterRenderer::prepareRender(glm::mat4 viewMatrix, glm::vec3 cameraPosition, Light sun) {
	shader->start();
	shader->loadViewMatrix(viewMatrix, cameraPosition);
	moveFactor += WAVE_SPEED * display->getFrameTimeSeconds();
	moveFactor = fmod(moveFactor, 1); //make the movefactor loop back to zero when it goes above 1
	shader->loadMoveFactor(moveFactor);
	shader->loadLight(sun);
	glBindVertexArray(quad.get_VaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterFbos.getReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, waterFbos.getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dudvTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, normalMap);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, waterFbos.getRefractionDepthTexture());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
void WaterRenderer::unbind() {
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}
void WaterRenderer::setUpVAO(Loader loader) {
	//only x and z coords are set here. Y is et to 0 in vertex shader..
	float holdVertices[] = { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f };

	std::vector<float> vertices(holdVertices, holdVertices + sizeof(holdVertices) / sizeof(holdVertices[0])); //Convert it to a vector because arrays suck
	quad = loader.loadToVAO(vertices, 2); //store the quad into a vao

}

WaterRenderer::~WaterRenderer(void)
{
}
