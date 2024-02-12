#pragma once
#include "Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"
#include "DisplayManager.h"
#include "Maths.h"

class GuiRenderer
{
private:
	RawModel quad;
	GuiShader shaders;
	DisplayManager display;

public:
	GuiRenderer(Loader loader);

	void render(std::vector<GuiTexture> guis);

	void cleanUp();

	~GuiRenderer(void);
};

