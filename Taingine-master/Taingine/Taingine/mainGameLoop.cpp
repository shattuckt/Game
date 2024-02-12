
#include <GLFW/glfw3.h>
#include "TaingineThreads.h"
#include "DisplayManager.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "RawModel.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "objLoader.h"
#include "NormalMappedObjLoader.h"
#include "Camera.h"
#include "Light.h"
#include "Player.h"
#include "Mob.h"
#include "GuiTexture.h"
#include "GuiRenderer.h"
#include "MousePicker.h"
#include "WaterShader.h"
#include "WaterRenderer.h"
#include "WaterFrameBuffers.h"
#include "TextMaster.h"
#include "ParticleMaster.h"
#include "ParticleSystem.h"
#include "Runable.h"
#include <iostream>

//In vertex shader, it will produce a color for each vertex inputted, in this case it would be 4 vertices. 
//create a class that implements the java version of the shader. it should be similar to shader.h which is from learnopengl.com.. 

int main() {
	DisplayManager* display = new DisplayManager();
	display->createDisplay();

	Loader loader;
	objLoader ObjLoader;
	NormalMappedObjLoader NMloader;

	//Loads text
	TextMaster textMaster;
	textMaster.init(loader, display);

	FontType* font = new FontType(loader.loadTexture("vinerHand.png", 0.0f), "vinerHand.fnt",display);
	std::string screenText = "doo doo performace v1.0";
	GUIText* text = new GUIText(screenText, 1, font, glm::vec2(0, 0), 0.5f, false);
	textMaster.loadText(text);

	//***********Terrain Texture Things*******
	int debugTextureID = loader.loadTexture("debugTexture.png", -0.4f);
	int greenAfTextureID = loader.loadTexture("greenAf.png", -0.4f);
	TerrainTexture backgroundTexture = TerrainTexture(debugTextureID);
	TerrainTexture rTexture = TerrainTexture(debugTextureID);
	TerrainTexture gTexture = TerrainTexture(debugTextureID);
	TerrainTexture bTexture = TerrainTexture(debugTextureID);

	TerrainTexturePack* texturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
	TerrainTexture blendMap = TerrainTexture(loader.loadTexture("blendMap.png", -0.4f));
	//***********************************************

	TexturedModel rocks = TexturedModel(ObjLoader.loadObj("rocks.obj", loader), ModelTexture(loader.loadTexture("rocks.png", -0.4f)));

	ModelTexture fernTextureAtlas = ModelTexture(loader.loadTexture("atlas-fern.png", -0.4f));
	fernTextureAtlas.setNumberOfRows(2);

	TexturedModel fern = TexturedModel(ObjLoader.loadObj("fern.obj", loader), fernTextureAtlas);
	TexturedModel pine = TexturedModel(ObjLoader.loadObj("pine.obj", loader), ModelTexture(loader.loadTexture("pine.png", -0.4f)));
	pine.getTexture().setHasTransparency(true);
	fern.getTexture().setHasTransparency(true);

	std::vector<Terrain*> terrains;
	HeightsGenerator* heightsGenerator = new HeightsGenerator();
	for (int i = -2; i < 2; i++) {
		for (int j = -2; j < 2; j++) {
			Terrain* terrain = new Terrain(i, j, loader, texturePack, blendMap, "heightmap", heightsGenerator);
			terrains.push_back(terrain);
		}

	}

	TexturedModel lamp = TexturedModel(ObjLoader.loadObj("lamp.obj", loader), ModelTexture(loader.loadTexture("lamp.png", -0.4f)));
	lamp.getTexture().setuseFakeLighting(true);

	std::vector<Entity*> entities;
	std::vector<Entity*> normalMappedEntities;

	//************************************************NORMAL MAPPED MODELS**************************************
	TexturedModel barrelModel = TexturedModel(NMloader.loadObj("barrel.obj", loader), ModelTexture(loader.loadTexture("barrel.png", -0.4f), loader.loadTexture("barrelNormal.png", -0.4f)));
	barrelModel.getTexture().setShineDamper(10);
	barrelModel.getTexture().setReflectivity(0.5f);

	TexturedModel crateModel = TexturedModel(NMloader.loadObj("crate.obj", loader), ModelTexture(loader.loadTexture("crate.png", -0.4f), loader.loadTexture("crateNormal.png", -0.4f)));
	crateModel.getTexture().setShineDamper(10);
	crateModel.getTexture().setReflectivity(0.5f);

	TexturedModel boulderModel = TexturedModel(NMloader.loadObj("boulder.obj", loader), ModelTexture(loader.loadTexture("boulder.png", -0.4f), loader.loadTexture("boulderNormal.png", -1.4f)));
	boulderModel.getTexture().setShineDamper(10);
	boulderModel.getTexture().setReflectivity(0.5f);

	TexturedModel cyborgModel = TexturedModel(NMloader.loadObj("cyborg.obj", loader), ModelTexture(loader.loadTexture("cyborg_diffuse.png", -0.4f), loader.loadTexture("cyborg_normal.png", -0.4f)));
	cyborgModel.getTexture().setShineDamper(10);
	cyborgModel.getTexture().setReflectivity(0.5f);

	//******************************************************ENTITIES *******************************************
	normalMappedEntities.push_back(new Entity(barrelModel, 0, glm::vec3(-10, 10, 40), 0, 0, 0, 1.0f));
	normalMappedEntities.push_back(new Entity(boulderModel, 0, glm::vec3(0, 10, 40), 0, 0, 0, 1.0f));
	normalMappedEntities.push_back(new Entity(crateModel, 0, glm::vec3(10, 10, 40), 0, 0, 0, 0.04f));
	normalMappedEntities.push_back(new Entity(cyborgModel, 0, glm::vec3(20, 10, 40), 0, 0, 0, 5.04f));

	int maxCoord = 4000;
	std::string key;
	float x, y, z;
	for (int i = 0; i < 1000; i++) {
		if (i % 3 == 0) {
			x = (rand() % maxCoord * 2) - maxCoord;
			z = (rand() % maxCoord * 2) - maxCoord;
			
			key = std::to_string(x).append("-").append(std::to_string(z));
			y = TerrainHeights::terrainHeights[key];
			normalMappedEntities.push_back(new Entity(boulderModel, 3, glm::vec3(x, y, z), rand() % 360, rand() % 360, rand() % 360, rand() % 5));
			
		}
		if (i % 2 == 0) {
			x = (rand() % maxCoord * 2) - maxCoord;
			z = (rand() % maxCoord * 2) - maxCoord;
			key = std::to_string(x).append("-").append(std::to_string(z));
			y = TerrainHeights::terrainHeights[key];
			entities.push_back(new Entity(pine, 1, glm::vec3(x, y, z), 0, rand() % 360, 0, rand() % 2 + 2));
		}
	}
	//entities.push_back(new Entity(rocks, 0, glm::vec3(75, 4.6f, -75), 0, 0, 0, 75));

	//***********************************Lights, player
	std::vector<Light> lights;
	Light sun = Light(glm::vec3(10000, 10000, -10000), glm::vec3(1.3f, 1.3f, 1.3f));
	lights.push_back(sun);

	

	TexturedModel player1 = TexturedModel(ObjLoader.loadObj("person.obj", loader), ModelTexture(loader.loadTexture("playerTexture.png", -0.4f)));
	Player* player = new Player(player1, 0, glm::vec3(0, 0, 0), 0, 100, 0, 0.6f, display->getWindow());
	
	Camera* camera = new Camera(display->getWindow(), display, player);
	player->setCamera(camera);
	player->setDisplay(display);

	entities.push_back(player);
	entities.push_back(player);

	std::vector <GuiTexture> guiTextures;
	GuiRenderer guiRenderer = GuiRenderer(loader);

	MasterRenderer renderer(display, loader, camera);
	MousePicker picker = MousePicker(display->getWindow(), camera, renderer.getProjectionMatrix(), player, display);

	//*******************Particle setup*************************
	//std::vector<Particle*> particles;
	//ParticleTexture* particleTexture = new ParticleTexture(loader.loadTexture("planetParticle.png", -0.4f), 1);
	ParticleTexture* particleTexture = new ParticleTexture(loader.loadTexture("particleAtlas.png", -0.4f), 4, false);
	ParticleMaster* particleMaster = new ParticleMaster(loader, renderer.getProjectionMatrix());
	ParticleSystem* system = new ParticleSystem(particleTexture, 500, 10, 0.1f, 1, 1, display);

	ParticleTexture* planetTexture = new ParticleTexture(loader.loadTexture("planetParticle.png", -0.4f), 1, false);
	ParticleSystem* planets = new ParticleSystem(planetTexture, 500, 10, 0.1f, 1, 1, display);

	system->setScaleError(0.5f);

	//****************Water Renderer Set-Up**********************
	WaterFrameBuffers waterFbos = WaterFrameBuffers(display);
	WaterShader waterShader;
	waterShader.WaterShaders();
	WaterRenderer waterRenderer = WaterRenderer(loader, &waterShader, renderer.getProjectionMatrix(), waterFbos, display);
	std::vector<WaterTile> waters;
	WaterTile water = WaterTile(0, -15, 0);
	waters.push_back(water);

	//GuiTexture refraction = GuiTexture(waterFbos.getRefractionTexture(), glm::vec2(0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
	//GuiTexture reflection = GuiTexture(waterFbos.getReflectionTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
	//guis.push_back(refraction);
	//guis.push_back(reflection);

	//This will actually greate a small gui that will render the custom FBO inside of it 
	//GuiTexture gui = GuiTexture(waterFbos.getReflectionTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, 0.5f));
	//guis.push_back(gui); //You can render these things to anything you want, not just a gui.
	//HOWEVER, make sure you dont render anything that is going to be rendered on the texture

	int fps = 0;
	//*************************************Game loop below ********************************
	while (!glfwWindowShouldClose(display->getWindow())) {

		//fps = fps + 1;
		//GUIText* fpsText = new GUIText("fps - ", 1, font, glm::vec2(0.5f, 0.5f), 0.5f, false);
		//textMaster.loadText(fpsText);
		
		//The following four lines resizes the window. Talk to Taylor if there is any cleaner solution... 
		int width, height;
		glfwGetWindowSize(display->getWindow(), &width, &height);

		display->setWidth(width);


		display->setHeight(height);

		key = std::to_string((int)player->getPosition().x).append("-").append(std::to_string((int)player->getPosition().z));
		//std::cout << "Height using key : " << key << " = " << TerrainHeights::terrainHeights[key] << std::endl;
		player->move(camera->getAngleAroundPlayer(), TerrainHeights::terrainHeights[key]);
		//player->move(camera->getAngleAroundPlayer());
		camera->move();
		picker.update(); 

		//std::cout << "Player position: " << player->getPosition().x << " / " << player->getPosition().y << " / " << player->getPosition().z << std::endl;

		normalMappedEntities[0]->increaseRotation(0, 1, 0);
		normalMappedEntities[1]->increaseRotation(0, 1, 0);
		normalMappedEntities[2]->increaseRotation(0, 1, 0);
		normalMappedEntities[3]->increaseRotation(0, 1, 0);

		if (glfwGetKey(display->getWindow(), GLFW_KEY_T) == GLFW_PRESS) {
			std::cout << "Toggling debug texture for terrain" << std::endl;
			int textureToUse = texturePack->getBackgroundTexture().getTextureID() == debugTextureID ? greenAfTextureID : debugTextureID;
			texturePack->setBackgroundTexture(textureToUse);
			texturePack->setrTexture(textureToUse);
			texturePack->setgTexture(textureToUse);
			texturePack->setbTexture(textureToUse);
		}

		//system->generateParticles(particles, player->getPosition());
		//system->generateParticles(particles, glm::vec3(0, 0, 0));
		particleMaster->generateParticles(system, glm::vec3(0, 20, 0));
		//particleMaster->generateParticles(planets, glm::vec3(20, 20, 0));
		particleMaster->update(camera);

		glEnable(GL_CLIP_DISTANCE0);
		
		//Every frame we need to render to one of our FBOs. We need to bind the buffer we want to render...
		waterFbos.bindReflectionFrameBuffer(); //Render the reflection buffer 
											   //Before we bind the reflection texture (the one below the water), we need to invert the camera and move it below the ground equal to how high above it was originally.
		float distance = 2 * (camera->getCameraPosition().y - water.getHeight());
		
		camera->setCameraPosition(glm::vec3(camera->getCameraPosition().x, camera->getCameraPosition().y - distance, camera->getCameraPosition().z)); //Set the camera to the new position
		camera->invertPitch();
		renderer.renderScene(entities, normalMappedEntities, terrains, lights, camera, display, glm::vec4(0, 1, 0, -water.getHeight() + 1.0f)); //Render only things above the water - NOTE: adding 1.0f at the end of both renders allows for a little wiggle room for error so the edges dont glitch out NOTE NOTE: THIS WILL CAUSE THINGS TO REFLECT THAT ARENT SUPPOSED TO SO KEEP IT AS SMALL AS POSSIBLE 
		camera->setCameraPosition(glm::vec3(camera->getCameraPosition().x, camera->getCameraPosition().y + distance, camera->getCameraPosition().z)); //Set the camera to the new position
		camera->invertPitch(); //return the camera back to its inverted position
		
		//Render refraction texture
		waterFbos.bindRefractionFrameBuffer();
		renderer.renderScene(entities, normalMappedEntities, terrains, lights, camera, display, glm::vec4(0, -1, 0, water.getHeight())); //render everything under the water.

	   //render to the screen
		//Note: the following 3d and 2d objects never clear. So, to update them you need to clear out the vectors and then fill them with new objects...
		glDisable(GL_CLIP_DISTANCE0); //this is supposed to make it where the main screen has no clip planes... but sometimes this command just gets ignored... 
		waterFbos.unbindCurrentFrameBuffer();
		renderer.renderScene(entities, normalMappedEntities, terrains, lights, camera, display, glm::vec4(0, -1, 0, 100000)); //clip plane was all zeros before? //Render all the 3D objects in the scene
		waterRenderer.render(waters, camera->getViewMatrix(), camera->getCameraPosition(), sun); //this only takes in 1 light atm (the sun)
		

		//std::unordered_map<std::string, std::thread*>::iterator testIter = TaingineThreads::taingineThreads.find("particleThread");
		//if (testIter != TaingineThreads::taingineThreads.end()) {
		//	testIter->second->join();
		//}
		particleMaster->renderParticles(camera);
		

		guiRenderer.render(guiTextures); //render your gui textures.. 
		textMaster.render(); //render all texts
		
		//textMaster.removeText(fpsText);

		display->updateDisplay();

	}

	particleMaster->cleanUp();
	textMaster.cleanUp(); 
	waterFbos.cleanUp(); //Delete all water FBOs
	waterShader.cleanUp(); //Delete water shaders 
	guiRenderer.cleanUp(); //Clean up all the gui textures...
	renderer.cleanUp(); //clean up the shaders
	loader.cleanUp(); //Clean up all the VAOs and VBOs

						 //Close the display
	display->closeDisplay();

}
