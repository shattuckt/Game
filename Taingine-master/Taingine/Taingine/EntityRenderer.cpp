#include "EntityRenderer.h"
#include <Windows.h>


EntityRenderer::EntityRenderer(StaticShader shader, DisplayManager* newDisplay, glm::mat4 projectionMatrix)
{
	shaders = shader; //Set the shader so it can be accessed in the below functions
	display = newDisplay; //set the display so it can be accessed in the below functions 
	shaders.start(); //start the shader so the projectionmatrix can be loaded 
	shaders.loadProjectionMatrix(projectionMatrix); //Load the projection matrix
	shaders.stop(); //stop the shader since we are done using it fow now
}



void EntityRenderer::render(std::unordered_map<entityDef, std::vector<Entity>, hash_entity, equal_entity> entities) {
	for (std::unordered_map<entityDef, std::vector<Entity>, hash_entity, equal_entity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		TexturedModel model(it->first.first, it->first.second); //not sure if this creates another model or not... 

		prepareTexturedModel(model); //enable the texture and such

		std::vector<Entity> entityBatch = entities.at(entityDef(it->first.first, it->first.second));
		//At this point we have batch holding each entity within that key (model type)
		//So we need to loop through each entity affiliated with the TexturedModel type.. any amount of stall.obj for example 
		for (std::vector<Entity>::iterator itSec = entityBatch.begin(); itSec != entityBatch.end(); ++itSec) {
			Entity tester(itSec->getModel(), itSec->getTextureIndex(), itSec->getPosition(), itSec->getRotX(), itSec->getRotY(), itSec->getRotZ(), itSec->getScale());
			//std::cout << "The renderer is attempting to bind " << model.getRawModel().get_VertexCount() << " vertices" << std::endl;
			prepareInstance(tester);
			glDrawElements(GL_TRIANGLES, model.getRawModel().get_VertexCount(), GL_UNSIGNED_INT, 0);

		}
		//Then we need to unbind the texturedModel of concern (whatever the type we were previously rendering 
		unbindTexturedModel();
	}
}

void EntityRenderer::prepareTexturedModel(TexturedModel model) {
	RawModel rawModel = model.getRawModel(); //This fetches the ID for the raw model of the entity's object type.. stall's vao id for example
											 //std::cout << "inside the Renderer::prepareTexturedModel, the vaoID is " << rawModel.get_VaoID() << std::endl;

	glBindVertexArray(rawModel.get_VaoID());  //you have to bind vaos and vbos before you can use them
	glEnableVertexAttribArray(0); //enable the attribute that the array is stored.. so zero
	glEnableVertexAttribArray(1); //enable the texture attribute list
	glEnableVertexAttribArray(2); //enable the normals 

	ModelTexture texture = model.getTexture(); //get the texture

	shaders.loadNumberOfRows(texture.getNumberofRows()); //Load the number of textures (well rows but we find it from that amount) found inside the single texture... (atlas textures)

	if (texture.getHasTransparency() == 1) {
		//std::cout << "Texture with ID: " << model.getTexture().getID() << " contains transparency " << std::endl;
		glDisable(GL_CULL_FACE); //NOTE THIS IS ONLY HEAR BECAUSE I DONT KNOW HOW TO CALL THE DISABLE FUNCTION IN THE MASTERRENDERER FROM HERE
	}
	shaders.loadShineVariables(texture.getShineDamper(), texture.getReflectivity()); //loads the shine variables (it is used directly in the shaders and is a bound attribute)

	glActiveTexture(GL_TEXTURE0); //Activate texture
	glBindTexture(GL_TEXTURE_2D, texture.getID()); //Bind the texture
}

void EntityRenderer::unbindTexturedModel() {
	//THE following two lines of code should also be done from the masterrenderer but im not sure how to call the function from here
	glEnable(GL_CULL_FACE);//The following prevents faces not pointing at the camera from rendering 
	glCullFace(GL_BACK); //cull meaning "do not render" the back of the faces.. 


	glDisableVertexAttribArray(0); //once finished, disable the attribute list you enabled
	glDisableVertexAttribArray(1); //once finished, disable the attribute list you enabled
	glDisableVertexAttribArray(2); //once finished, disable the attribute list you enabled
	glBindVertexArray(0);  //unbind the vao you binded. 
}


//The below method is updated for each entity. so if there are variables that need to be loaded in the shader for each entity OF ONE TYPE (because maybe they change in size or atlas texture for example)
void EntityRenderer::prepareInstance(Entity entity) {
	Maths math; //This line and the next two are for loading and using the transformationMatrix
	glm::mat4 transformationMatrix = math.createTransformationMatrix(entity.getPosition(), entity.getRotX(),
		entity.getRotY(), entity.getRotZ(), entity.getScale());
	//std::cout << glm::to_string(transformationMatrix) << std::endl;
	//unsigned int tester = glGetUniformLocation(shader.get_programID(), "transformationMatrix");
	shaders.loadTransformationMatrix(transformationMatrix); //This is the same as 'setINT' in - it calls glUniformMatrix4(, false, matrixBuffer);
	shaders.loadOffset(entity.getTextureXOffset(), entity.getTextureYOffset()); //load the offset for that entity's atlas texture.. if any  

}
