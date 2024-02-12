#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "NormalMappingShader.h"
#include <glm-0.9.8.5\glm\glm.hpp>
#include <math.h>
#include <unordered_map>

typedef pair<RawModel, ModelTexture> entityDefs;

struct hash_entitys { //This is meant to return the hash of all 5 elements 
	size_t operator()(const entityDefs& entitydef) const {
		RawModel rawmodel = entitydef.first;
		ModelTexture texture = entitydef.second;
		return hash<int>()(rawmodel.get_VaoID()) ^ hash<int>()(rawmodel.get_VertexCount()) ^
			hash<int>()(texture.getID()) ^ hash<float>()(texture.getReflectivity()) ^ hash<float>()(texture.getShineDamper());
	}
};

struct equal_entitys { //We now need to find if they are all equal or not... 
	bool operator()(const entityDefs& lhs, const entityDefs& rhs) const {
		RawModel leftrawmodel = lhs.first;
		RawModel rightrawmodel = rhs.first;
		ModelTexture lefttexture = lhs.second;
		ModelTexture righttexture = rhs.second;
		return leftrawmodel.get_VaoID() == rightrawmodel.get_VaoID() && leftrawmodel.get_VertexCount() == rightrawmodel.get_VertexCount() &&
			lefttexture.getID() == righttexture.getID() && lefttexture.getReflectivity() == righttexture.getReflectivity() &&
			lefttexture.getShineDamper() == righttexture.getShineDamper();
	}
};

class NormalMappingRenderer
{
private:

	NormalMappingShader shader;

public:




	NormalMappingRenderer(NormalMappingShader shader, glm::mat4 projectionMatrix);
	NormalMappingRenderer() {};

	void render(std::unordered_map<entityDefs, std::vector<Entity>, hash_entitys, equal_entitys> entities, glm::vec4 clipPlane, std::vector<Light> lights, glm::mat4 viewMatrix);
	void prepareTexturedModel(TexturedModel model);
	void unbindTexturedModel();
	void prepareInstance(Entity entity);
	void prepare(glm::vec4 clipPlane, std::vector<Light> lights, glm::mat4 viewMatrix);
	void cleanUp();
	//glm::mat4 createViewMatrix(Camera* camera);


	~NormalMappingRenderer(void);
};

