#include "MasterRenderer.h"
//The purpose of this class is to only call the render method once for all aspects of one model
//In other words, if you create a hundred cubes using the same vao, this class will make all of the cubes
//render with only binding the VAO and its attributes ONCE instead of a hundred times PER FRAME... 

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 10000;

//The following RGB is for the fog color... 
const float RED = 1; //0.5444f;
const float BLUE = 1; //0.62f;
const float GREEN = 1; //0.69f;

MasterRenderer::MasterRenderer(DisplayManager* newDisplay, Loader loader, Camera* camera) {
	//StaticShader shader; //Initialize the entity shader
	TerrainShader tshader; //Initialize the terrain shader
	NormalMappingShader nshader; //initialize the normal mapping shader
	//enableCulling();
	//shader.StaticShaders(); //load and bind the entity shader 
	tshader.TerrainShaders(); //load and bind the terrain shader
	nshader.normalMappingShaders(); //load and bind the normal mapping shader

	entityShaders = new StaticShader(); //store the entity shader in the MasterRenderer
	entityShaders->StaticShaders();





	terrainShaders = tshader; //store the terrain shader in the MasterRenderer 
	normalMapShaders = nshader; //store the normal mapping shader int the masterRenderer
	display = newDisplay; //store the passed display in the MasterRenderer

	createProjectionMatrix(); //Create the projection matrix 
	this->camera = camera;

	NormalMappingRenderer normalMapRenderers(normalMapShaders, projectionMatrix);
	normalMapRenderer = normalMapRenderers;

	EntityRenderer newRenderers(*entityShaders, display, projectionMatrix); //load the projection matrix into the entity renderer
	entityRenderer = newRenderers; //store the entity renderer in the MasterRenderer

	TerrainRenderer terrainRenderers(terrainShaders, display, projectionMatrix); //load the projection matrix into the terrain rendererr
	terrainRenderer = terrainRenderers;

	SkyboxRenderer skyboxRenderers(loader, projectionMatrix);
	skyboxRenderer = skyboxRenderers;



}


void MasterRenderer::enableCulling() {
	glEnable(GL_CULL_FACE);//The following prevents faces not pointing at the camera from rendering 
	glCullFace(GL_BACK); //cull meaning "do not render" the back of the faces.. 
}

void MasterRenderer::disableCulling() {
	glDisable(GL_CULL_FACE); //This is used in order to implement transparent objects 
}

//The following method processes all terrains and entities for the current scene. Finally, it renders the light and camera
void MasterRenderer::renderScene(std::vector<Entity*> entities, std::vector<Entity*> normalMapEntities, std::vector<Terrain*> terrains, std::vector<Light> lights, Camera* camera, DisplayManager* display, glm::vec4 clipPlane) {
	for (unsigned int i = 0; i < terrains.size(); i++) {
		processTerrain(terrains[i]);
	}
	for (unsigned int i = 0; i < entities.size(); i++) {
		processEntity(*entities[i]);
	}
	for (unsigned int i = 0; i < normalMapEntities.size(); i++) {
		processNormalMapEntity(*normalMapEntities[i]);
	}
	render(lights, camera, display, clipPlane);
}

#pragma region render(std::vector<Light>, Camera, DisplayManager, clipPlane)
/// <summary> Call rendering functions for all entity types </summary>
/// <param name="lights"> Lights needing to be rendered for this scene </param>
/// <returns> void </returns>
void MasterRenderer::render(std::vector<Light> lights, Camera* camera, DisplayManager* display, glm::vec4 clipPlane) {
	prepare();
	entityShaders->start();
	entityShaders->loadClipPlane(clipPlane);
	entityShaders->loadSkyColour(RED, GREEN, BLUE);
	entityShaders->loadLights(lights);
	entityShaders->loadViewMatrix(camera->getViewMatrix());
	entityRenderer.render(entities);
	entityShaders->stop();
	normalMapRenderer.render(normalMapEntities, clipPlane, lights, camera->getViewMatrix());
	terrainShaders.start();
	terrainShaders.loadClipPlane(clipPlane);
	terrainShaders.loadSkyColour(RED, GREEN, BLUE);
	terrainShaders.loadLights(lights);
	terrainShaders.loadViewMatrix(camera->getViewMatrix());
	terrainRenderer.render(terrains);
	terrainShaders.stop();

	skyboxRenderer.render(camera->getViewMatrix(), display, RED, GREEN, BLUE); //rgb is passed into the renderer since it is the fog colour 

	terrains.clear();
	entities.clear();
	normalMapEntities.clear();

}
#pragma endregion

void MasterRenderer::processTerrain(Terrain* terrain) {
	terrains.push_back(terrain);
}
#pragma region processEntity(Entity entity)
/// This does alot of things, it will check if there is already a model type (based on the hash produces from the 
/// vaoID, vertexCount, TextureID, Shine, and Damp) and either create a new hash entry or append it to a currently existing hash (collision)
/// NOTE: THERE SHOULD BE COLLISIONS AS LONG AS THE TEXTUREDMODELS ARE THE SAME. ENTITY ELEMENTS DO NOT MATTER.
void MasterRenderer::processEntity(Entity entity) {
	TexturedModel entityModel = entity.getModel(); //Get the model from the entity 
	entities[entityDef(entityModel.getRawModel(), entityModel.getTexture())].push_back(entity);
}
#pragma endregion
void MasterRenderer::processNormalMapEntity(Entity entity) {
	TexturedModel entityModel = entity.getModel();
	normalMapEntities[entityDef(entityModel.getRawModel(), entityModel.getTexture())].push_back(entity);
}

void MasterRenderer::cleanUp() {
	entityShaders->cleanUp();
	terrainShaders.cleanUp();
	normalMapRenderer.cleanUp();
}

void MasterRenderer::prepare() {

	glEnable(GL_DEPTH_TEST); //This prevents shapes in the background from rendering in the foreground. i dont see why you would ever not want this active. 
	glClearColor(RED, GREEN, BLUE, 1);  //This makes a blue background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->createViewMatrix(); //This updates the viewMatrix for all the rendering classes
	createProjectionMatrix();

}

void MasterRenderer::createProjectionMatrix() {

	//const float FOV = 70;  //70 degrees?
	//const float NEAR_PLANE = 0.1f;
	//const float FAR_PLANE = 1000;
	const double pi = 3.14159265358979323846;

	//I'm not sure what these do but they are elements of the projectionMatrix itself
	float aspectRatio = (float)display->getWidth() / (float)display->getHeight();
	float y_scale = (float)(1.0f / tan(FOV / 2.0f));
	float x_scale = y_scale / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;  //This is ZM. 

													//The following creates the projectionMatrix and then assigns the above values and some others.. 
	projectionMatrix[0][0] = x_scale;
	projectionMatrix[1][1] = y_scale;
	projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
	projectionMatrix[3][3] = 0;

	//Camera newCamera;
	//DisplayManager dm;
	//projectionMatrix = glm::perspective(glm::radians(newCamera.getFov()), (float)dm.getWidth() / (float)dm.getHeight(), 0.1f, 100.0f);

}


glm::mat4 MasterRenderer::getProjectionMatrix() {
	return projectionMatrix;
}

MasterRenderer::~MasterRenderer(void)
{
}

