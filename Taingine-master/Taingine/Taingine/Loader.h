#pragma once
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <vector>
//#include <iostream>
//#include <string>
#include <Windows.h>
#include "RawModel.h"
#include "getPaths.h"
#include "TextureData.h"
//#include "stb_image.h"

class Loader
{
private:

	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;

	//Define iterators for these vectors
	typedef std::vector <GLuint>::iterator vaosIter;
	typedef std::vector <GLuint>::iterator vbosIter;

public:
	Loader();


	RawModel loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices);
	RawModel loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<float> tangents, std::vector<unsigned int> indices);
#pragma region 	int loadToVAO(std::vector<float> positions, std::vector<float> textureCoords)
	/// Loader for text data
	int loadToVAO(std::vector<float> positions, std::vector<float> textureCoords);
#pragma endregion

	RawModel loadToVAO(std::vector<float> positions, int dimensions); //i dont think this is used.

	int createEmptyVbo(int floatCount);

	void addInstancedAttribute(int vaoID, int vboID, int attribute, int dataSize, int instancedDataLength, int offset);

	void updateVbo(int vboID, std::vector<float> data);
	
	TextureData processTexture(std::string fileName);



	int loadCubeMap(std::vector<std::string> textureFiles);

#pragma region 	int loadToVAO(std::vector<float> positions, std::vector<float> textureCoords)
	/// Load text fileName (ex: box.png)
	/// bias - the mipmapping bias desired
	///		negative bias is sharper where zero is smoother
	///     NOTE: More negative just means itll render higher resolution textures for objects
	///                further back which means the game will run slower.
	int loadTexture(std::string fileName, float bias);
#pragma endregion

	void cleanUp();

	int createVAO();

	void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> data);

	void bindIndicesBuffer(std::vector<unsigned int> indices);

	void unbindVAO();

	~Loader(void);
};



