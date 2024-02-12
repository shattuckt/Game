#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "getPaths.h"
#include "Vertex.h"
#include "ModelData.h"
#include "Loader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class objLoader
{
private:
	std::vector<Vertex*> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> finalVertices;
	std::vector<float> finalTextures;
	std::vector<float> finalNormals;

public:
	objLoader(void);

	RawModel loadObj(std::string objFileName, Loader loader);
	Vertex* processVertex(glm::vec3 currentFacePart);
	Vertex* dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex);
	void removeUnusedVertices(std::vector<Vertex*> vertices);
	float convertDataToArrays(std::vector<Vertex*> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals);

	~objLoader();
};

