//The following function creates two FBO objects - one for refraction and one for reflection
//These are used to texture the water objects in the render engine. 
#include "WaterFrameBuffers.h"

const int REFLECTION_WIDTH = 320;
const int REFLECTION_HEIGHT = 180;

const int REFRACTION_WIDTH = 1280;
const int REFRACTION_HEIGHT = 720;

WaterFrameBuffers::WaterFrameBuffers(DisplayManager* displays) {
	display = displays; //set the display manager pointer
	initializeReflectionFrameBuffer();
	initializeRefractionFrameBuffer();
}

void WaterFrameBuffers::cleanUp() {
	glDeleteFramebuffers(1, &reflectionFrameBuffer);
	glDeleteTextures(1, &reflectionTexture);
	glDeleteRenderbuffers(1, &reflectionDepthBuffer);
	glDeleteFramebuffers(1, &refractionFrameBuffer);
	glDeleteTextures(1, &refractionTexture);
	glDeleteTextures(1, &refractionDepthTexture);

}

//The following function binds the reflection FBO before it is rendererd 
void WaterFrameBuffers::bindReflectionFrameBuffer() {
	bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

//The following function binds the refraction FBO before it is rendererd
void WaterFrameBuffers::bindRefractionFrameBuffer() {
	bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

//The following switches back to the default frame buffer
//NOTE: This HAS to be called if you use a custom FBO or else nothing will render onto the screen. 
void WaterFrameBuffers::unbindCurrentFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, display->getWidth(), display->getHeight());
}

//The following function returns the reflection texture
int WaterFrameBuffers::getReflectionTexture() {
	return reflectionTexture;
}

//The following function returns the refraction texture
int WaterFrameBuffers::getRefractionTexture() {
	return refractionTexture;
}

//The following function returns the second refraction texture - the depth texture
int WaterFrameBuffers::getRefractionDepthTexture() {
	return refractionDepthTexture;
}

//The following initializes the reflection FBO
void WaterFrameBuffers::initializeReflectionFrameBuffer() {
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();

}

//The following initializes the refraction FBO
void WaterFrameBuffers::initializeRefractionFrameBuffer() {
	refractionFrameBuffer = createFrameBuffer();
	refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
}


//This binds the FBO (make sure to switch it back to default when done)
//NOTE: This function allows us to choose which frame buffer we want the engine to render to - either the core FBO or one of our own
void WaterFrameBuffers::bindFrameBuffer(int frameBuffer, int width, int height) {
	glBindTexture(GL_TEXTURE_2D, 0); //just to make sure not texture is bound
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer); //bind the buffer we want the engine to render to 
	glViewport(0, 0, width, height);                //pass the resolution of this buffer
}

//The following creates a FrameBuffer object and returns its ID
//THIS IS THE FOUNDATION FOR THE FRAME BUFFER. The core frame buffer is how images are represented on the screen. These secondary frame buffers do not render anything onto the screen
//ALSO, think of this createFrameBuffer as a mr. potato and you are then adding the color attachments (like his arms or something... one arm...) and depth attachments (like his legs.. also one leg..)
unsigned int WaterFrameBuffers::createFrameBuffer() {
	unsigned int frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer); //have to bind it to use it
	glDrawBuffer(GL_COLOR_ATTACHMENT0); //NOTE: If you ever want to use more than one color buffer, this will have to be able to bind more than just the first color buffer
	return frameBuffer;
}

//the followiing method creates a texture attachment and returns it's ID
unsigned int WaterFrameBuffers::createTextureAttachment(int width, int height) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0); //this adds the texture object to the currently bound buffer object. Note last parameter only changes when mipmaps are used in the texture. 
	return texture;
}

//The following functions create the depth texture as well as the buffer for that texture
unsigned int WaterFrameBuffers::createDepthTextureAttachment(int width, int height) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0); //Instead of a color attachment, we are now binding the texture to a depth attachment. 
	return texture;
}
//Render buffers are NON-texture attachments. 
unsigned int WaterFrameBuffers::createDepthBufferAttachment(int width, int height) {
	unsigned int depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height); //We will be storing depth information in this non-texture attachment (render buffer)
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer); //Then we attach the attachment nto the current bound frame buffer. 
	return depthBuffer;
}


WaterFrameBuffers::~WaterFrameBuffers(void) {
}
