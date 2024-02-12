#pragma once
#include "RawModel.h"
#include "ModelTexture.h"


class TexturedModel
{

private:

	RawModel rawModel;
	ModelTexture texture;

public:
	TexturedModel(RawModel model, ModelTexture textures);

	TexturedModel(void) {}

	RawModel getRawModel();

	ModelTexture getTexture();

	~TexturedModel(void);
};
