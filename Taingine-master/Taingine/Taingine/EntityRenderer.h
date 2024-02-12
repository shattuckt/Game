#pragma once
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "RawModel.h"
//#include "TexturedModel.h"
#include "DisplayManager.h"
#include "StaticShader.h"
#include "Maths.h"
//#include <glm-0.9.8.5\glm\glm.hpp>
//#include <glm-0.9.8.5\glm\mat4x4.hpp>
//#include <glm-0.9.8.5\glm\matrix.hpp>
//#include <glm-0.9.8.5\glm\gtx\string_cast.hpp>
//#include "Maths.h"
#include "Entity.h"
//#include <iostream>
//#include <math.h>
#include <unordered_map>
//#include <list>

typedef pair<RawModel, ModelTexture> entityDef;

struct hash_entity { //This is meant to return the hash of all 5 elements 
	size_t operator()(const entityDef& entitydef) const {
		RawModel rawmodel = entitydef.first;
		ModelTexture texture = entitydef.second;
		return hash<int>()(rawmodel.get_VaoID()) ^ hash<int>()(rawmodel.get_VertexCount()) ^
			hash<int>()(texture.getID()) ^ hash<float>()(texture.getReflectivity()) ^ hash<float>()(texture.getShineDamper());
	}
};

struct equal_entity { //We now need to find if they are all equal or not... 
	bool operator()(const entityDef& lhs, const entityDef& rhs) const {
		RawModel leftrawmodel = lhs.first;
		RawModel rightrawmodel = rhs.first;
		ModelTexture lefttexture = lhs.second;
		ModelTexture righttexture = rhs.second;
		return leftrawmodel.get_VaoID() == rightrawmodel.get_VaoID() && leftrawmodel.get_VertexCount() == rightrawmodel.get_VertexCount() &&
			lefttexture.getID() == righttexture.getID() && lefttexture.getReflectivity() == righttexture.getReflectivity() &&
			lefttexture.getShineDamper() == righttexture.getShineDamper();
	}
};
class EntityRenderer
{
private:

	StaticShader shaders;
	DisplayManager* display;

public:
	EntityRenderer(StaticShader shader, DisplayManager* newDisplay, glm::mat4 projectionMatrix);
	EntityRenderer() {}; //added this as a default constructor 
	void render(std::unordered_map<entityDef, std::vector<Entity>, hash_entity, equal_entity> entities);
	void prepareTexturedModel(TexturedModel model);
	void unbindTexturedModel();
	void prepareInstance(Entity entity);


};

