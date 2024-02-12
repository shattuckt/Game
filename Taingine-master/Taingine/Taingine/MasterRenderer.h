#pragma once
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "TerrainShader.h"
#include "NormalMappingRenderer.h"
#include "SkyboxRenderer.h"
#include <unordered_map>
#include <list>
//The purpose of this class is to only call the render method once for all aspects of one model
//In other words, if you create a hundred cubes using the same vao, this class will make all of the cubes
//render with only binding the VAO and its attributes ONCE instead of a hundred times PER FRAME... 

class MasterRenderer
{

private:
	glm::mat4 projectionMatrix;

#pragma region objectVariables
	Camera* camera;
	StaticShader* entityShaders = NULL;
	EntityRenderer entityRenderer;
	DisplayManager* display;
	TerrainRenderer terrainRenderer;
	TerrainShader terrainShaders;
	NormalMappingRenderer normalMapRenderer;
	NormalMappingShader normalMapShaders;
	SkyboxRenderer skyboxRenderer;
#pragma endregion

	std::unordered_map<entityDef, std::vector<Entity>, hash_entity, equal_entity> entities; //the key pair definition, the list of entities, the hash struct, and the isEqual struct
	std::unordered_map<entityDefs, std::vector<Entity>, hash_entitys, equal_entitys> normalMapEntities; //the key pair definition, the list of entities, the hash struct, and the isEqual struct
	std::vector<Terrain*> terrains;

public:
	MasterRenderer(DisplayManager* newDisplay, Loader loader, Camera* camera);
	MasterRenderer(void) {};
	void renderScene(std::vector<Entity*> entities, std::vector<Entity*> normalMapEntities, std::vector<Terrain*> terrains, std::vector<Light> lights, Camera* camera, DisplayManager* display, glm::vec4 clipPlane);
	void render(std::vector<Light> lights, Camera* camera, DisplayManager* display, glm::vec4 clipPlane);
	void processTerrain(Terrain* terrain);
	void processEntity(Entity entity);
	void processNormalMapEntity(Entity entity);
	void cleanUp();
	void prepare();
	void createProjectionMatrix();
	glm::mat4 getProjectionMatrix();
	//void createViewMatrix(Camera* camera);
	static void enableCulling();
	static void disableCulling();
	~MasterRenderer(void);

};

