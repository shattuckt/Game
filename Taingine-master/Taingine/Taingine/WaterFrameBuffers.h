#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "DisplayManager.h"

class WaterFrameBuffers
{
private:
	unsigned int reflectionFrameBuffer;
	unsigned int reflectionTexture;
	unsigned int reflectionDepthBuffer;

	unsigned int refractionFrameBuffer;
	unsigned int refractionTexture;
	unsigned int refractionDepthTexture;

	DisplayManager* display; //needed to swithc viewport back to default

public:
	WaterFrameBuffers(DisplayManager* display);
	WaterFrameBuffers(void) {};

	void cleanUp();

	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();


	int getReflectionTexture();
	int getRefractionTexture();
	int getRefractionDepthTexture();
	void initializeReflectionFrameBuffer();
	void initializeRefractionFrameBuffer();

	void bindFrameBuffer(int frameBuffer, int width, int height);
	unsigned int createFrameBuffer();
	unsigned int createTextureAttachment(int width, int height);
	unsigned int createDepthTextureAttachment(int width, int height);
	unsigned int createDepthBufferAttachment(int width, int height);

	~WaterFrameBuffers(void);
};

