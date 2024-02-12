#pragma once
#include <unordered_map>
#include "Camera.h"
#include "RawModel.h"
#include "Loader.h"
#include "Maths.h"
#include "ParticleShader.h"
#include "Particle.h"

struct hash_particleMap {
	size_t operator()(ParticleTexture* texture) const {
		return hash<int>()(texture->getTextureID()) ^ hash<int>()(texture->getNumberOfRows());
	}
};

struct equal_particleMap {
	bool operator()(ParticleTexture* lhs, ParticleTexture* rhs) const {
		return lhs->getNumberOfRows() == rhs->getNumberOfRows() && lhs->getTextureID() == rhs->getTextureID();
	}
};

class ParticleRenderer
{
private:
	RawModel quad;
	ParticleShader* shader;

	Loader loader;
	Maths math;
	int vboID;

	std::vector<float> vboData;

public:
	ParticleRenderer(Loader loader, glm::mat4 projectionMatrix);

	void render(std::unordered_map<ParticleTexture*, std::vector<Particle*>, hash_particleMap, equal_particleMap> &particles, Camera* camera);
	void cleanUp();
	void updateTexCoordInfo(Particle* particle, std::vector<float> &data);
	void bindTexture(ParticleTexture* texture);
	void updateModelViewMatrix(glm::vec3 position, float rotation, float scale, glm::mat4 viewMatrix, std::vector<float> &vboData);
	void storeMatrixData(glm::mat4 matrix, std::vector<float>& vboData);
	void prepare();
	void finishRendering();
};

