#include "TexturedModel.h"


TexturedModel::TexturedModel(RawModel model, ModelTexture textures)
{
	rawModel = model;
	texture = textures;


}

RawModel TexturedModel::getRawModel() {

	return rawModel;

}

ModelTexture TexturedModel::getTexture() {

	return texture;

}


TexturedModel::~TexturedModel(void)
{
}
