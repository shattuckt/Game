#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "getPaths.h"
#include "VertexNM.h"
#include "Loader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm-0.9.8.5\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.5\glm\gtx\string_cast.hpp>

class NormalMappedObjLoader
{
private:
	std::vector<VertexNM*> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> finalVertices;
	std::vector<float> finalTextures;
	std::vector<float> finalNormals;
	std::vector<float> finalTangents;
	
public:
	NormalMappedObjLoader(void);

	RawModel loadObj(std::string objFileName, Loader loader);
	//void calculateTangents(VertexNM* v0, VertexNM* v1, VertexNM* v2, std::vector<VertexNM*> vertices, std::vector<glm::vec2> textures);
	void calculateTangents(VertexNM* v0, VertexNM* v1, VertexNM* v2, std::vector<glm::vec2> textures);
	//VertexNM* processVertex(glm::vec3 currentFacePart, std::vector<VertexNM *> vertices, std::vector<unsigned int>* indices);
	VertexNM* processVertex(glm::vec3 currentFacePart);
	//VertexNM* dealWithAlreadyProcessedVertex(VertexNM* previousVertex, int newTextureIndex, int newNormalIndex,
		//std::vector<unsigned int>* indices, std::vector<VertexNM*> vertices);
	VertexNM* dealWithAlreadyProcessedVertex(VertexNM* previousVertex, int newTextureIndex, int newNormalIndex);
	void removeUnusedVertices(std::vector<VertexNM*> vertices);
	float convertDataToArrays(std::vector<VertexNM*> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals);

	~NormalMappedObjLoader();
};

