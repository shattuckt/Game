#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RawModel
{
private:
	int vaoIDs;
	int vertexCounts;

public:
	RawModel(int vaoID, int vertexCount);

	RawModel(void) {};

	int get_VaoID();

	int get_VertexCount();

	~RawModel();

};

