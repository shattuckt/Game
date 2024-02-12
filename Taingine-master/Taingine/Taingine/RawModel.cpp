#include "RawModel.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

//Constructor logic
RawModel::RawModel(int vaoID, int vertexCount) {

	cout << "Raw Model Created -> vaoID = " << vaoID << " vertexCount = " << vertexCount << endl;
	vaoIDs = vaoID;
	vertexCounts = vertexCount;


}

int RawModel::get_VaoID() {

	return vaoIDs;

}

int RawModel::get_VertexCount() {

	return vertexCounts;

}

RawModel::~RawModel() {



}
