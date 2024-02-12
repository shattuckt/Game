#include "TerrainRenderer.h"


TerrainRenderer::TerrainRenderer(TerrainShader shader, DisplayManager* newDisplay, glm::mat4 projectionMatrix) {

	shaders = shader;
	display = newDisplay;
	shaders.start();
	shaders.loadProjectionMatrix(projectionMatrix);
	shaders.connectTextureUnits();
	shaders.stop();

}

void TerrainRenderer::render(std::vector<Terrain*> terrains) {
	for (int i = 0; i < terrains.size(); i++) {
		prepareTerrain(terrains[i]);
		loadModelMatrix(terrains[i]);
		glDrawElements(GL_TRIANGLES, terrains[i]->getModel().get_VertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain(Terrain* terrain) {
	RawModel rawModel = terrain->getModel(); //This fetches the ID for the raw model of the entity's object type.. stall's vao id for example
											//std::cout << "inside the Renderer::prepareTexturedModel, the vaoID is " << rawModel.get_VaoID() << std::endl;

	glBindVertexArray(rawModel.get_VaoID());  //you have to bind vaos and vbos before you can use them
	glEnableVertexAttribArray(0); //enable the attribute that the array is stored.. so zero
	glEnableVertexAttribArray(1); //enable the texture attribute list
	glEnableVertexAttribArray(2); //enable the normals 

	bindTextures(terrain);
	shaders.loadShineVariables(1, 0); //loads the shine variables (it is used directly in the shaders and is a bound attribute)

}

void TerrainRenderer::bindTextures(Terrain* terrain) {
	TerrainTexturePack* texturePack = terrain->getTexturePacks();
	glActiveTexture(GL_TEXTURE0); //Activate texture
	glBindTexture(GL_TEXTURE_2D, texturePack->getBackgroundTexture().getTextureID()); //Bind the texture
	glActiveTexture(GL_TEXTURE1); //Activate texture
	glBindTexture(GL_TEXTURE_2D, texturePack->getrTexture().getTextureID()); //Bind the texture
	glActiveTexture(GL_TEXTURE2); //Activate texture
	glBindTexture(GL_TEXTURE_2D, texturePack->getgTexture().getTextureID()); //Bind the texture
	glActiveTexture(GL_TEXTURE3); //Activate texture
	glBindTexture(GL_TEXTURE_2D, texturePack->getbTexture().getTextureID()); //Bind the texture
	glActiveTexture(GL_TEXTURE4); //Activate texture
	glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap().getTextureID()); //Bind the texture

}

void TerrainRenderer::unbindTexturedModel() {
	glDisableVertexAttribArray(0); //once finished, disable the attribute list you enabled
	glDisableVertexAttribArray(1); //once finished, disable the attribute list you enabled
	glDisableVertexAttribArray(2); //once finished, disable the attribute list you enabled
	glBindVertexArray(0);  //unbind the vao you binded. 
}

void TerrainRenderer::loadModelMatrix(Terrain* terrain) {
	Maths math; //This line and the next two are for loading and using the transformationMatrix
	//std::cout << "Terrain x and y coords to transform: " << terrain->getX() << "/" << terrain->getZ() << std::endl;
	glm::mat4 transformationMatrix = math.createTransformationMatrix(glm::vec3(terrain->getX(), 0, terrain->getZ()), 0, 0, 0, 1);
	//std::cout << glm::to_string(transformationMatrix) << std::endl;
	//unsigned int tester = glGetUniformLocation(shader.get_programID(), "transformationMatrix");
	shaders.loadTransformationMatrix(transformationMatrix); //This is the same as 'setINT' in - it calls glUniformMatrix4(, false, matrixBuffer);

}

void TerrainRenderer::run() {

}

TerrainRenderer::~TerrainRenderer(void)
{
}
