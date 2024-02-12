#include "SkyboxRenderer.h"

const float BOXSIZE = 5000.0f;

const float VERTICESARR[] = {
	-BOXSIZE,  BOXSIZE, -BOXSIZE,
	-BOXSIZE, -BOXSIZE, -BOXSIZE,
	BOXSIZE, -BOXSIZE, -BOXSIZE,
	BOXSIZE, -BOXSIZE, -BOXSIZE,
	BOXSIZE,  BOXSIZE, -BOXSIZE,
	-BOXSIZE,  BOXSIZE, -BOXSIZE,

	-BOXSIZE, -BOXSIZE,  BOXSIZE,
	-BOXSIZE, -BOXSIZE, -BOXSIZE,
	-BOXSIZE,  BOXSIZE, -BOXSIZE,
	-BOXSIZE,  BOXSIZE, -BOXSIZE,
	-BOXSIZE,  BOXSIZE,  BOXSIZE,
	-BOXSIZE, -BOXSIZE,  BOXSIZE,

	BOXSIZE, -BOXSIZE, -BOXSIZE,
	BOXSIZE, -BOXSIZE,  BOXSIZE,
	BOXSIZE,  BOXSIZE,  BOXSIZE,
	BOXSIZE,  BOXSIZE,  BOXSIZE,
	BOXSIZE,  BOXSIZE, -BOXSIZE,
	BOXSIZE, -BOXSIZE, -BOXSIZE,

	-BOXSIZE, -BOXSIZE,  BOXSIZE,
	-BOXSIZE,  BOXSIZE,  BOXSIZE,
	BOXSIZE,  BOXSIZE,  BOXSIZE,
	BOXSIZE,  BOXSIZE,  BOXSIZE,
	BOXSIZE, -BOXSIZE,  BOXSIZE,
	-BOXSIZE, -BOXSIZE,  BOXSIZE,

	-BOXSIZE,  BOXSIZE, -BOXSIZE,
	BOXSIZE,  BOXSIZE, -BOXSIZE,
	BOXSIZE,  BOXSIZE,  BOXSIZE,
	BOXSIZE,  BOXSIZE,  BOXSIZE,
	-BOXSIZE,  BOXSIZE,  BOXSIZE,
	-BOXSIZE,  BOXSIZE, -BOXSIZE,

	-BOXSIZE, -BOXSIZE, -BOXSIZE,
	-BOXSIZE, -BOXSIZE,  BOXSIZE,
	BOXSIZE, -BOXSIZE, -BOXSIZE,
	BOXSIZE, -BOXSIZE, -BOXSIZE,
	-BOXSIZE, -BOXSIZE,  BOXSIZE,
	BOXSIZE, -BOXSIZE,  BOXSIZE
};


const std::string DAY_TEXTURE_FILESARR[] = { "sRight.png", "sLeft.png", "sUp.png", "sDown.png", "sBack.png", "sFront.png" };
//const std::string DAY_TEXTURE_FILESARR[] = { "dayRight.png", "dayLeft.png", "dayTop.png", "dayBottom.png", "dayBack.png", "dayFront.png" };
//const std::string DAY_TEXTURE_FILESARR[] = { "nightRight.png", "nightLeft.png", "nightTop.png", "nightBottom.png", "nightBack.png", "nightFront.png" };
const std::string NIGHT_TEXTURE_FILESARR[] = { "nightRight.png", "nightLeft.png", "nightTop.png", "nightBottom.png", "nightBack.png", "nightFront.png" };
SkyboxRenderer::SkyboxRenderer(Loader loader, glm::mat4 projectionMatrix) {
	time = 0;
	loaded = loader;
	//std::vector<float> VERTICES(VERTICESARR, VERTICESARR + sizeof(VERTICESARR) / sizeof(VERTICESARR[0]));
	std::vector<float> VERTICES; //make a vector then insert the vertices array into it... 
	VERTICES.insert(VERTICES.end(), &VERTICESARR[0], &VERTICESARR[sizeof(VERTICESARR) / sizeof(int)]);
	cube = loaded.loadToVAO(VERTICES, 3);

	std::vector<std::string> DAY_TEXTURE_FILES(DAY_TEXTURE_FILESARR, DAY_TEXTURE_FILESARR + sizeof(DAY_TEXTURE_FILESARR) / sizeof(DAY_TEXTURE_FILESARR[0]));           //put the day textures in a vec 
	std::vector<std::string> NIGHT_TEXTURE_FILES(NIGHT_TEXTURE_FILESARR, NIGHT_TEXTURE_FILESARR + sizeof(NIGHT_TEXTURE_FILESARR) / sizeof(NIGHT_TEXTURE_FILESARR[0])); //put the night textures in a vec
	dayTexture = loaded.loadCubeMap(DAY_TEXTURE_FILES); //load the day textures into a vao 
	nightTexture = loaded.loadCubeMap(NIGHT_TEXTURE_FILES); //load the night textures into a vao 

	SkyboxShader skyShader;
	skyShader.SkyboxShaders();
	shaders = skyShader;
	shaders.start();
	shaders.connectTextureUnits();                                         //tell the shader which sampler units to use whenever rendering the night and day boxes. 
	shaders.loadProjectionMatrix(projectionMatrix);
	shaders.stop();
}

void SkyboxRenderer::render(glm::mat4 viewMatrix, DisplayManager* display, float r, float g, float b) {
	shaders.start();
	shaders.loadViewMatrix(viewMatrix, display);
	shaders.loadFogColour(r, g, b);                                         //load the fog colour to the shader (uniform variable)
	glBindVertexArray(cube.get_VaoID());                                    //bind the VAO we want to use... 
	glEnableVertexAttribArray(0);                                           //zero is where the textures are stored
	bindTextures(display);                                                         //this method activates and binds all cube maps (right now there is only day and night... 1 for each) 
	glDrawArrays(GL_TRIANGLES, 0, cube.get_VertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shaders.stop();

}

void SkyboxRenderer::bindTextures(DisplayManager* display) { //more than two textures could be used. could even change the fog color based on what the time of day is... obviously the time is between 0 and 24000.
	time += display->getFrameTimeSeconds() * 100;                         //Directly controls how quickly the day changes. * 1000 = day swap every couple seconds. 
	time = fmod(time, 24000);
	int texture1;
	int texture2;
	float blendFactor;
	//std::cout << "Inside skyboxRenderer::bindTextures, time is " << time << std::endl;
	if (time >= 0 && time < 5000) {                             //make both boxes to the night texture. 
		texture1 = nightTexture;
		texture2 = nightTexture;
		blendFactor = (time - 0) / (5000 - 0);
	}
	else if (time >= 5000 && time < 8000) {                    //blend them equally 
		texture1 = nightTexture;
		texture2 = dayTexture;
		blendFactor = (time - 5000) / (8000 - 5000);
	}
	else if (time >= 8000 && time < 21000) {                    //make both boxes to the day texture 
		texture1 = dayTexture;
		texture2 = dayTexture;
		blendFactor = (time - 8000) / (21000 - 8000);
	}
	else {
		texture1 = dayTexture;
		texture2 = nightTexture;
		blendFactor = (time - 21000) / (24000 - 21000);
	}
	glActiveTexture(GL_TEXTURE0);                          //activate the first spot for the texture... 
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);        //bind the day texture cube map
	glActiveTexture(GL_TEXTURE1);                          //activate teh next spot for the texture... 
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);      //bind the night texture cube map 
	shaders.loadBlendFactor(blendFactor);                         //tell the shader how the two maps should be mixed... literally blended together. 0.5 means the two maps will be blended equally together 

}

SkyboxRenderer::~SkyboxRenderer(void)
{
}
