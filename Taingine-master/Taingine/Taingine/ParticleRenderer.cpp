#include "ParticleRenderer.h"

const std::vector<float> VERTICES = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
const int MAX_INSTANCES = 10000;
const int INSTANCE_DATA_LENGTH = 9; // this is the amount of floats required to store all the information for one vertex.

ParticleRenderer::ParticleRenderer(Loader loader, glm::mat4 projectionMatrix) {
	this->loader = loader;
	this->quad = this->loader.loadToVAO(VERTICES, 2);
	this->vboID = loader.createEmptyVbo(MAX_INSTANCES * INSTANCE_DATA_LENGTH); //the total number of possible floats needed to store all data.
	loader.addInstancedAttribute(quad.get_VaoID(), vboID, 1, 3, INSTANCE_DATA_LENGTH, 0); // Vertex position
	loader.addInstancedAttribute(quad.get_VaoID(), vboID, 2, 1, INSTANCE_DATA_LENGTH, 3); // Scale
	loader.addInstancedAttribute(quad.get_VaoID(), vboID, 3, 4, INSTANCE_DATA_LENGTH, 4); // TextureOffset
	loader.addInstancedAttribute(quad.get_VaoID(), vboID, 4, 1, INSTANCE_DATA_LENGTH, 8); // Blend factor

	this->math = Maths();

	this->shader = new ParticleShader();
	shader->fontShaders();
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void ParticleRenderer::render(std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap> &particles, Camera* camera) {
	prepare();
	
	for (std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap>::iterator it = particles.begin(); it != particles.end(); ++it) {
		std::vector<Particle*> particleList = particles.at(it->first);
		bindTexture(it->first);
		shader->loadViewMatrix(camera->getViewMatrix());

		this->vboData.clear();

		//for (std::vector<Particle*>::iterator partListIt = particleList.begin(); partListIt != particleList.end(); ++it) {
		for (int i = 0; i < particleList.size(); i++){

			//std::cout << "Particle: " << (*partListIt)->getPosition().x << "/" << (*partListIt)->getPosition().y << "/" << (*partListIt)->getPosition().z <<
				//"\n rotation: " << (*partListIt)->getRotation() << "\n Scale: " << (*partListIt)->getScale() << std::endl;
			//std::cout << "Particle: " << particleList[i]->getPosition().x << "/" << particleList[i]->getPosition().y << "/" << particleList[i]->getPosition().z <<
				//"\n rotation: " << particleList[i]->getRotation() << "\n Scale: " << particleList[i]->getScale() << std::endl;
			//updateModelViewMatrix(particleList[i]->getPosition(), particleList[i]->getRotation(), particleList[i]->getScale(), viewMatrix, vboData);
			updateTexCoordInfo(particleList[i], vboData);
			//std::cout << "ParticleRenderer quad.get_vertexCount = " << quad.get_VertexCount() << std::endl;
		}
		loader.updateVbo(vboID, vboData);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad.get_VertexCount(), particleList.size());
	}
	finishRendering();
}

void ParticleRenderer::cleanUp() {
	this->shader->cleanUp();
}

void ParticleRenderer::updateTexCoordInfo(Particle* particle, std::vector<float> &data) {
	data.push_back(particle->getPosition().x);
	data.push_back(particle->getPosition().y);
	data.push_back(particle->getPosition().z);
	data.push_back(particle->getScale());
	data.push_back(particle->getTexOffset1().x);
	data.push_back(particle->getTexOffset1().y);
	data.push_back(particle->getTexOffset2().x);
	data.push_back(particle->getTexOffset2().y);
	data.push_back(particle->getBlend());
}

void ParticleRenderer::bindTexture(ParticleTexture* texture) {
	if (texture->usesAdditiveBlending()) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	else {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	shader->loadNumberOfRows(texture->getNumberOfRows());
}

void ParticleRenderer::updateModelViewMatrix(glm::vec3 position, float rotation, float scale, glm::mat4 viewMatrix, std::vector<float> &vboData) {
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);

	std::cout << "ModelViewMatrix: \n" << glm::to_string(modelMatrix) << std::endl;

	//The following is how rotation is getting canceled out in the viewMatrix. So no rotation is applied to the particle
	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));

	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	//std::cout << "ModelViewMatrix: " << modelViewMatrix[0][0] << "/" << modelViewMatrix[0][1] << "/" << modelViewMatrix[0][2] << "/" << modelViewMatrix[0][3] << "\n" <<
		//modelViewMatrix[1][0] << "/" << modelViewMatrix[1][1] << "/" << modelViewMatrix[1][2] << "/" << modelViewMatrix[1][3] << "\n" <<
		//modelViewMatrix[2][0] << "/" << modelViewMatrix[2][1] << "/" << modelViewMatrix[2][2] << "/" << modelViewMatrix[2][3] << "\n" <<
		//modelViewMatrix[3][0] << "/" << modelViewMatrix[3][1] << "/" << modelViewMatrix[3][2] << "/" << modelViewMatrix[3][3] << std::endl;
	//shader->loadModelViewMatrix(modelViewMatrix);
	storeMatrixData(modelViewMatrix, vboData);
}

void ParticleRenderer::storeMatrixData(glm::mat4 matrix, std::vector<float>& vboData) {
	vboData.push_back(matrix[0][0]);
	vboData.push_back(matrix[0][1]);
	vboData.push_back(matrix[0][2]);
	vboData.push_back(matrix[0][3]);
	vboData.push_back(matrix[1][0]);
	vboData.push_back(matrix[1][1]);
	vboData.push_back(matrix[1][2]);
	vboData.push_back(matrix[1][3]);
	vboData.push_back(matrix[2][0]);
	vboData.push_back(matrix[2][1]);
	vboData.push_back(matrix[2][2]);
	vboData.push_back(matrix[2][3]);
	vboData.push_back(matrix[3][0]);
	vboData.push_back(matrix[3][1]);
	vboData.push_back(matrix[3][2]);
	vboData.push_back(matrix[3][3]);
}

void ParticleRenderer::prepare() {
	shader->start();
	//std::cout << "Prepare quad - its VaoId: " << quad.get_VaoID() << std::endl;
	glBindVertexArray(quad.get_VaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnable(GL_BLEND);
	glDepthMask(false); //prevents rendering to the depth buffer

}

void ParticleRenderer::finishRendering() {
	glDepthMask(true); //prevents rendering to the depth buffer
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindVertexArray(0);
	shader->stop();
}